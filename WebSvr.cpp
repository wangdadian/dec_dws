
#include "WebSvr.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "define.h"
//----------------------------------------------------------------------------
// WebSvr.cpp                                                                  
//----------------------------------------------------------------------------

// 配置对象，全局
static CDWConfig* g_pDWConfig;
static CEWConfig* g_pEWConfig;
// 保存IP地址
char g_szIp[64];
// 最大用户数
const unsigned int MAX_USER = 16;
// 用户数据
TuserLocation g_userLocation[MAX_USER];
// 用户最大不操作时间（秒），超过则注销用户
const long MAX_NO_OPERATE_TIME = 3600;
// 记录用户最后操作时间
int g_iLastOpTime[MAX_USER];

//////////////////////////////////////////////////////////////////////////

int CWebSvr::m_iUpgradeRet = 0;
int CWebSvr::m_iNetworkRet = 0;
int CWebSvr::m_iSysinfoRet = 0;
CWebSvr::CWebSvr() 
{    
    rootWeb = T("www");			/* Root web directory */
	password = T("");			/* Security password */
	port = 80;					/* Server port */
	retries = 5;				/* Server port retries */	

    m_pDWConfig = new CDWConfig;
    assert(m_pDWConfig!=NULL);
    g_pDWConfig = m_pDWConfig;

    m_pEWConfig = new CEWConfig;
    assert(m_pEWConfig!=NULL);
    g_pEWConfig = m_pEWConfig;
    m_bExitFlag = false;
}

CWebSvr::~CWebSvr() 
{    
    m_bExitFlag = true;
    if( m_thCheckUser != 0 )
    {
        pthread_join(m_thCheckUser, NULL);
    }

    PTR_DELETE(m_pDWConfig);
    g_pDWConfig = NULL;
    PTR_DELETE(m_pEWConfig);
    g_pEWConfig = NULL;

}

void CWebSvr::init() 
{
    for(unsigned int i=0; i<MAX_USER; i++)
    {
        g_userLocation[i].ip[0] = '\0';
        g_userLocation[i].flag = -1;
        g_userLocation[i].user[0] = '\0';
        g_iLastOpTime[i] = 0;
    }

	//printf("init webs ...\n");
	get_ip(g_szIp);
	//printf("ip = %s\n",g_szIp);

    pthread_create(&m_thCheckUser, NULL, ThCheckUser, (void*)this);

	pthread_t  HttpThread;
	pthread_create(&HttpThread, NULL, Http_thread, this);		

	pthread_detach(HttpThread);
}
void * CWebSvr::ThCheckUser(void * param)
{
    CWebSvr* pThis = (CWebSvr*)param;
    while ( pThis->m_bExitFlag != true )
    {
        CFacility::SleepMsec(2000);
        pThis->CheckUser();
    }
    return NULL;
}
void CWebSvr::CheckUser()
{
    long iTime = time(NULL);
    long iTimeInt = 0;
    for(unsigned int i=0; i<MAX_USER; i++)
    {
        if(strcmp(g_userLocation[i].ip, "\0") != 0 && g_iLastOpTime[i] > 0)
        {
            iTimeInt = iTime - g_iLastOpTime[i];
            // 注销用户
            if ( iTimeInt > MAX_NO_OPERATE_TIME )
            {
                strcpy(g_userLocation[i].ip, "\0");
                g_userLocation[i].flag = -1;
                strcpy(g_userLocation[i].user, "\0");
                g_iLastOpTime[i] = 0;
            }
        }
    }
}
void * CWebSvr::Http_thread(void * param) 
{
    CWebSvr* theThread = static_cast<CWebSvr*>(param);
    theThread->thttpd_start_main();
    return NULL;
}

int CWebSvr::thttpd_start_main()
{
	/*
 *	Initialize the memory allocator. Allow use of malloc and start 
 *	with a 60K heap.  For each page request approx 8KB is allocated.
 *	60KB allows for several concurrent page requests.  If more space
 *	is required, malloc will be used for the overflow.
 */
 	//printf("*****************in http!***************\n");
	bopen(NULL, (60 * 1024), B_USE_MALLOC);
	signal(SIGPIPE, SIG_IGN);

/*
 *	Initialize the web server
 */
	if (initWebs() < 0)
	{
		//printf("call initWebs() failed!\n");
		return -1;
	}

#ifdef WEBS_SSL_SUPPORT
	websSSLOpen();
#endif

/*
 *	Basic event loop. SocketReady returns true when a socket is ready for
 *	service. SocketSelect will block until an event occurs. SocketProcess
 *	will actually do the servicing.
 */
	//while (!finished)
	while(1)
	{
		if (socketReady(-1) || socketSelect(-1, 1000))
		{
			socketProcess(-1);
		}
		websCgiCleanup();
		emfSchedProcess();	
	}

#ifdef WEBS_SSL_SUPPORT
	websSSLClose();
#endif
    
#ifdef USER_MANAGEMENT_SUPPORT
    umClose();
#endif
/*
 *	Close the socket module, report memory leaks and close the memory allocator
 */
 //printf("### close web server !!!\n");
 
	websCloseServer();
	socketClose();

	bclose();
	return 0;
}

	
/******************************************************************************/
/*
 *	Initialize the web server.
 */
int CWebSvr::initWebs()
{
//	struct hostent	*hp;
	struct in_addr	intaddr;
	char			host[128], dir[128], webdir[128];
	char			*cp;
	char_t			wbuf[128];

/*
 *	Initialize the socket subsystem
 */
	socketOpen();
    
#ifdef USER_MANAGEMENT_SUPPORT
    /*
    *	Initialize the User Management database
    */
    umOpen();
    umRestore(T("umconfig.txt"));
#endif
/*
 *	Define the local Ip address, host name, default home page and the 
 *	root web directory.
 */

/*
 *	Set ../web as the root web. Modify this to suit your needs
 */

	getcwd(dir, sizeof(dir)); 
	
	if ((cp = strrchr(dir, '.')))
	{
		*cp = '\0';
	}
	
	sprintf(webdir, "%s/%s", dir, rootWeb);

/*
 *	Configure the web server options before opening the web server
 */
	websSetDefaultDir(webdir);

	cp = inet_ntoa(intaddr);

	ascToUni(wbuf, cp, min(strlen(cp) + 1, sizeof(wbuf)));
	websSetIpaddr(wbuf);
	ascToUni(wbuf, host, min(strlen(host) + 1, sizeof(wbuf)));
	websSetHost(wbuf);

/*
 *	Configure the web server options before opening the web server
 */
	websSetDefaultPage(T("default.asp"));
	websSetPassword(password);

/* 
 *	Open the web server on the given port. If that port is taken, try
 *	the next sequential port for up to "retries" attempts.
 */
	//printf("web port is %d\n", port);
	websOpenServer(port, retries);

/*
 * 	First create the URL handlers. Note: handlers are called in sorted order
 *	with the longest path handler examined first. Here we define the security 
 *	handler, forms handler and the default web page handler.
 */
	websUrlHandlerDefine(T(""), NULL, 0, websSecurityHandler, 
	WEBS_HANDLER_FIRST);
	websUrlHandlerDefine(T("/goform"), NULL, 0, websFormHandler, 0);
	websUrlHandlerDefine(T("/cgi-bin"), NULL, 0, websCgiHandler, 0);
	websUrlHandlerDefine(T(""), NULL, 0, websDefaultHandler, 
	WEBS_HANDLER_LAST); 

/*
 *	Now define two test procedures. Replace these with your application
 *	relevant ASP script procedures and form functions.
 */
	websAspDefine(T("aspTest"), aspTest);
	websFormDefine(T("formTest"), formTest);
    
    // asp
    websAspDefine(T("asp_web_check_user"), aspWebCheckUser);
    websAspDefine(T("asp_clean_connect"), aspCleanConnect);
    websAspDefine(T("asp_get_ipaddr"), aspGetIpaddr);
    websAspDefine(T("asp_get_netmask"), aspGetNetmask);
    websAspDefine(T("asp_get_gateway"), aspGetGateway);
    websAspDefine(T("asp_get_sipsvr"), aspGetSipServer);
    websAspDefine(T("asp_get_user"), aspGetUser);
    websAspDefine(T("asp_get_dev_hostname"), aspGetHostname);
    websAspDefine(T("asp_get_dev_mac"), aspGetDevMAC);
    websAspDefine(T("asp_get_dev_model"), aspGetDevModel);
    websAspDefine(T("asp_get_dev_sn"), aspGetDevSN);
    websAspDefine(T("asp_get_dev_ver"), aspGetDevVer);
    websAspDefine(T("asp_get_dev_buildtime"), aspGetDevBuildtime);
    websAspDefine(T("asp_get_time"), aspGetTime);
    websAspDefine(T("asp_get_ntp"), aspGetNtp);
    websAspDefine(T("asp_get_dev_uptime"), aspGetUptime);
    websAspDefine(T("asp_get_upgrade_ret"), aspGetUpgradeRet);
    websAspDefine(T("asp_get_network_ret"), aspGetNetworkRet);
    websAspDefine(T("asp_get_sysinfo_ret"), aspGetSysinfoRet);
    websAspDefine(T("asp_get_resolution"), aspGetResolution);
    websAspDefine(T("asp_get_resolution_chn"), aspGetResolutionChn);
    websAspDefine(T("asp_get_chn_url"), aspGetChnDynamic);
    websAspDefine(T("asp_get_chn_fps"), aspGetChnFps);
	websAspDefine(T("asp_get_chn_code"), aspGetChnCode);
    websAspDefine(T("asp_get_user_list"), aspGetUserList);
    websAspDefine(T("asp_get_enc_display"), aspGetEncDisplay);
    websAspDefine(T("asp_get_enc_trans"), aspGetEncTransfer);
    websAspDefine(T("asp_get_enc_video"), aspGetEncVideo);
    websAspDefine(T("asp_get_enc_channel"), aspGetEncChannel);
    websAspDefine(T("asp_get_alarmin"), aspGetEncAlarmin);
    websAspDefine(T("asp_get_alarmout"), aspGetEncAlarmout);
    websAspDefine(T("asp_get_ptzport"), aspGetEncPtzPort);
    websAspDefine(T("asp_get_forwardport_info"), aspGetEncForwardPort);
    websAspDefine(T("asp_get_chn_cnt"), aspGetChannelCount);
    websAspDefine(T("asp_get_dec_osdshow"), aspGetDecOsdShow);
    websAspDefine(T("get_ping_ret"), aspGetPingRet);
	websAspDefine(T("get_ar_info"), aspGetARInfo);
    // form  
    websFormDefine(T("form_check_user"), formCheckUser);
    websFormDefine(T("form_exit_system"), formExitSystem);
    websFormDefine(T("form_network_config"), formNetworkConfig);
    websFormDefine(T("form_sipsvr"), formSetSipServer);
    websFormDefine(T("form_set_time"), formSetTime);
    websFormDefine(T("form_set_ntp"), formSetNtp);
    websFormDefine(T("form_set_sysinfo"), formSetSysInfo);
	websFormDefine(T("form_dev_setting"), formDevSetting);
    websFormDefine(T("form_dev_state"), formDevState);
    websFormDefine(T("form_dev_reboot"), formDevReboot);
    websFormDefine(T("form_dev_reset"), formDevReset);
    websFormDefine(T("form_dev_update"), formDevUpdate);
	websFormDefine(T("form_dec_set_channel"), formDecSetChannel);
    websFormDefine(T("form_dec_set_resolution"), formDecSetResolution);
    websFormDefine(T("form_dec_set_dynamic"), formDecSetChnDynamic);
    websFormDefine(T("form_user_edit"), formEditUserInfo);
    websFormDefine(T("form_enc_display"), formEncDisplay);
    websFormDefine(T("form_enc_transfer"), formEncTransfer);
    websFormDefine(T("form_enc_video"), formEncVideo);
    websFormDefine(T("form_enc_alarm"), formEncAlarm);
    websFormDefine(T("form_enc_channel"), formEncChannel);
    websFormDefine(T("form_enc_ptzport"), formEncPtzPort);
    websFormDefine(T("enc_forwardport_form"), formEncForwardport);
    websFormDefine(T("form_dec_osd"), formDecOsd);
    websFormDefine(T("form_dev_ping"), formPing);
	websFormDefine(T("form_restart_svr"), formRestartSvr);
	// 自动重启
	websFormDefine(T("form_ar"), fromAutoReboot);

    /*
    *	Create the Form handlers for the User Management pages
    */
#ifdef USER_MANAGEMENT_SUPPORT
    formDefineUserMgmt();
#endif
/*
 *	Create a handler for the default home page
 */
	websUrlHandlerDefine(T("/"), NULL, 0, websHomePageHandler, 0); 

	return 0;	
}

/******************************************************************************/
/*
 *	Home page handler
 */
int CWebSvr::websHomePageHandler(webs_t wp, char_t *urlPrefix, char_t *webDir,int arg, char_t *url, char_t *path, char_t *query)
{
/*
 *	If the empty or "/" URL is invoked, redirect default URLs to the home page
 */
	if (*url == '\0' || gstrcmp(url, T("/")) == 0)
	{
		websRedirect(wp, T("index.asp"));
		return 1;
	}
	return 0;
}

/******************************************************************************/
/*
 *	Test Javascript binding for ASP. This will be invoked when "aspTest" is
 *	embedded in an ASP page. See web/asp.asp for usage. Set browser to 
 *	"localhost/asp.asp" to test.
 */

int CWebSvr::aspTest(int eid, webs_t wp, int argc, char_t **argv)
{
	char_t	*name, *address;

	if (ejArgs(argc, argv, T("%s %s"), &name, &address) < 2)
	{
		websError(wp, 400, T("Insufficient args\n"));
		return -1;
	}
	return websWrite(wp, T("Name: %s, Address %s"), name, address);
}

/******************************************************************************/
/*
 *	Test form for posted data (in-memory CGI). This will be called when the
 *	form in web/forms.asp is invoked. Set browser to "localhost/forms.asp" to test.
 */

void CWebSvr::formTest(webs_t wp, char_t *path, char_t *query)
{
	char_t	*name, *address;

	name = websGetVar(wp, T("name"), T("Joe Smith")); 
	address = websGetVar(wp, T("address"), T("1212 Milky Way Ave.")); 

	websHeader(wp);
	websWrite(wp, T("<body><h2>Name: %s, Address: %s</h2>\n"), name, address);
	websFooter(wp);
	websDone(wp, 200);
}

/******************************************************************************/
/*
 *	Default error handler.  The developer should insert code to handle
 *	error messages in the desired manner.
 */

void CWebSvr::defaultErrorHandler(int etype, char_t *msg)
{
#if 0
	write(1, msg, gstrlen(msg));
#endif
}

/******************************************************************************/
/*
 *	Trace log. Customize this function to log trace output
 */

void CWebSvr::defaultTraceHandler(int level, char_t *buf)
{
/*
 *	The following code would write all trace regardless of level
 *	to stdout.
 */
#if 0
	if (buf)
	{
		write(1, buf, gstrlen(buf));
	}
#endif
}

/******************************************************************************/
/*
 *	Returns a pointer to an allocated qualified unique temporary file name.
 *	This filename must eventually be deleted with bfree();
 */
/*
char_t* websGetCgiCommName()
{
	char_t	*pname1, *pname2;

	pname1 = tempnam(NULL, T("cgi"));
	
	pname2 = bstrdup(B_L, pname1);
	free(pname1);
	return pname2;
}
*/
/******************************************************************************/
/*
 *	Launch the CGI process and return a handle to it.
 */
/*
int websLaunchCgiProc(char_t *cgiPath, char_t **argp, char_t **envp,char_t *stdIn, char_t *stdOut)
{
	int	pid, fdin, fdout, hstdin, hstdout, rc;

	fdin = fdout = hstdin = hstdout = rc = -1; 
	if ((fdin = open(stdIn, O_RDWR | O_CREAT, 0666)) < 0 ||
		(fdout = open(stdOut, O_RDWR | O_CREAT, 0666)) < 0 ||
		(hstdin = dup(0)) == -1 ||
		(hstdout = dup(1)) == -1 ||
		dup2(fdin, 0) == -1 ||
		dup2(fdout, 1) == -1)
	{
		goto DONE;
	}
		
 	rc = pid = fork();
 	if (pid == 0) {

		if (execve(cgiPath, argp, envp) == -1)
		{
			printf("content-type: text/html\n\n"
				   "Execution of cgi process failed\n");
		}
		exit (0);
	} 

DONE:
	if (hstdout >= 0)
	{
		dup2(hstdout, 1);
		close(hstdout);
	}
	if (hstdin >= 0)
	{
		dup2(hstdin, 0);
		close(hstdin);
	}
	if (fdout >= 0)
	{
		close(fdout);
	}
	if (fdin >= 0)
	{
		close(fdin);
	}
	return rc;
}
*/

/******************************************************************************/
/*
 *	Check the CGI process.  Return 0 if it does not exist; non 0 if it does.
 */
/*
int websCheckCgiProc(int handle)
{
	if (waitpid(handle, NULL, WNOHANG) == handle)
	{
		return 0;
	} 
	else 
	{
		return 1;
	}
}
*/

int CWebSvr::reboot()
{
	//printf("reboot system,please wait!\n");
    
    return 0;
}

void CWebSvr::get_ip(char *ip)	//读取系统实际IP
{
	int skfd;
	struct ifreq ifr;
	struct sockaddr addr;
	struct sockaddr *padd;
	struct sockaddr_in * aa;
	char *ifname = (char*)"eth0";
	skfd = socket(AF_INET, SOCK_DGRAM, 0);
	if( skfd < 0 )
	{
		//printf("socket error");
	}
	
	strcpy(ifr.ifr_name, ifname);
	if (ioctl(skfd, SIOCGIFFLAGS, &ifr) >= 0)
	{
		strcpy(ifr.ifr_name, ifname);
		if ( skfd >= 0 )
		{
			strcpy(ifr.ifr_name, ifname);
			ifr.ifr_addr.sa_family = AF_INET;
			if (ioctl(skfd, SIOCGIFADDR, &ifr) == 0) 
			{
				addr = ifr.ifr_addr;
				padd = &addr;
				aa = (struct sockaddr_in *)padd;
			//	printf("IP addr : %s\n",inet_ntoa(aa->sin_addr));
				strcpy(ip,inet_ntoa(aa->sin_addr));
			} 
            else
            {
    			//printf("Ip address not found");
            }
		}
	}
	
	close(skfd);
}

void CWebSvr::formCheckUser(webs_t wp, char_t *path, char_t *query)
{
    char szUserName[64] = {0};
    char szPassword[64] = {0};
    char *szIpAddr = NULL;
    long lRet = 0;
    long flag = 0;
    
    //判断登录用户数是否超出最大限制
    if(g_userLocation[MAX_USER-1].flag != -1 )	 
    {
        pageReload_index(wp, path, query);
    }

    szIpAddr = websGetRequestIpaddr(wp);
    sprintf( szUserName, websGetVar(wp, T("userid"), T("0")) );
    sprintf( szPassword, websGetVar(wp, T("password"), T("0")) );
    
    flag = g_pDWConfig->UserLogin(szUserName, szPassword);
    if ( lRet < 0 )
    {
        pageReload_index(wp, path, query);
        return;
    }
    else
    {
        pageReload_main(wp, path, query);
        UpdateLastOpTime(wp);
        for(unsigned int i=0;i<MAX_USER;i++)
        {
            if(strcmp(g_userLocation[i].ip, szIpAddr) == 0)
            {
                strcpy(g_userLocation[i].ip, szIpAddr);
                g_userLocation[i].flag = flag;
                sprintf(g_userLocation[i].user, szUserName);
                return;
            }	
        }
        
        for(unsigned int i=0;i<MAX_USER;i++)
        {
            if(strcmp(g_userLocation[i].ip, "\0") == 0)
            {
                strcpy(g_userLocation[i].ip, szIpAddr);
                g_userLocation[i].flag = flag;
                sprintf(g_userLocation[i].user, szUserName);
                return;
            }	
        }
        return;
    }
}

void CWebSvr::formExitSystem(webs_t wp, char_t *path, char_t *query)
{
    char *ipaddr;
    ipaddr = websGetRequestIpaddr(wp);
    
    //clear the user 
    for(unsigned int i=0; i<MAX_USER;i++)
    {
        if(strcmp(g_userLocation[i].ip, ipaddr) == 0)
        {
            strcpy(g_userLocation[i].ip, "\0");
            g_userLocation[i].flag = -1;
            strcpy(g_userLocation[i].user, "\0");
            g_iLastOpTime[i] = 0;
            break;
        }	
    }	
    pageReload_index(wp, path, query);	
}

void CWebSvr::formNetworkConfig(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    struNetworkInfo objNI, objGetNI;
    memset(&objNI, 0, sizeof(struNetworkInfo));

    sprintf(objNI.ip, websGetVar(wp, T("ipaddr"), T("0")) );
    sprintf(objNI.netmask, websGetVar(wp, T("netmask"), T("0")) );
    sprintf(objNI.gateway, websGetVar(wp, T("gateway"), T("0")) );

    lRet = g_pDWConfig->GetNetworkInfo(&objGetNI);
    if ( lRet == 0 ) {
        // 没有发生修改，则不提交
        if (strcmp(objNI.ip, objGetNI.ip) == 0 &&
            strcmp(objNI.netmask, objGetNI.netmask) == 0 &&
            strcmp(objNI.gateway, objGetNI.gateway) == 0) 
        {
            pageReload_network(wp, path, query);
            return;
        }
    }

    lRet = g_pDWConfig->SetNetworkInfo(&objNI);
    if (lRet == RET_FAILED) {
        m_iNetworkRet = 2;
    }
    else{
        m_iNetworkRet = 1;
    }
    pageReload_network(wp, path, query);
}
void CWebSvr::formSetSipServer(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    char szBuf[256] = {0};
    sprintf( szBuf, websGetVar(wp, T("submit_str"), T("0")) );
    g_pDWConfig->SetSipServer(szBuf);
    pageReload_network(wp, path, query);
}

void CWebSvr::formSetTime(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    char szTime[64] = {0};
    sprintf( szTime, websGetVar(wp, T("time"), T("0")) );
    g_pDWConfig->SetTime(szTime);
    pageReload_time(wp, path, query);
}
void CWebSvr::formSetNtp(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    char szBuf[200] = {0};
    sprintf( szBuf, websGetVar(wp, T("submit_ntp_str"), T("0")) );
    g_pDWConfig->SetNtp(szBuf);
    pageReload_time(wp, path, query);
}
void CWebSvr::formSetSysInfo(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    struSysInfo objSI;
    char szBuf[64]={0};
    bool bChangedName = false;
    memset(&objSI, 0, sizeof(struSysInfo));
    sprintf( objSI.name, websGetVar(wp, T("dev_name"), T("0")) );
    sprintf( objSI.mac, websGetVar(wp, T("dev_mac"), T("0")) );
    sprintf( objSI.model, websGetVar(wp, T("dev_model"), T("0")) );
    sprintf( objSI.sn, websGetVar(wp, T("dev_sn"), T("0")) );
    sprintf( objSI.ver, websGetVar(wp, T("dev_ver"), T("0")) );

    // 设置设备名称（主机名称）
    g_pDWConfig->GetHostname(szBuf);
    if ( strcmp(szBuf, objSI.name) != 0 &&
         strcmp(objSI.name, "0") != 0)
    {
        lRet = g_pDWConfig->SetHostname(objSI.name);
        if (lRet == RET_FAILED) {
            m_iSysinfoRet = 2;
        }
        else{
            m_iSysinfoRet = 1;
            bChangedName = true;
        }
    }
 
    // 设置MAC
    memset(szBuf, 0, sizeof(szBuf));
    g_pDWConfig->GetDeviceMAC(szBuf);
    if ( strncasecmp(szBuf, objSI.mac, strlen(szBuf)) != 0 &&
        strcmp(objSI.mac, "0") != 0)
    {
        if ( CFacility::bMAC(objSI.mac) ) {
            lRet = g_pDWConfig->SetDeviceMAC(objSI.mac);
            if (lRet == RET_FAILED) {
                m_iSysinfoRet = 2;
            }
            else{
                m_iSysinfoRet = 1;
            }
        }
        else{
            m_iSysinfoRet = 2;
        }
    }
    //设置设备序列号
    memset(szBuf, 0, sizeof(szBuf));
    g_pDWConfig->GetDeviceSN(szBuf);
    if ( strcmp(szBuf, objSI.sn) != 0 &&
        strcmp(objSI.sn, "0") != 0
        ) {
        lRet = g_pDWConfig->SetDeviceSN(objSI.sn);
        if (lRet == RET_FAILED) {
            m_iSysinfoRet = 2;
        }
        else{
            m_iSysinfoRet = 1;
        }
    }

    // 重定向
    memset(szBuf, 0, sizeof(szBuf));
    sprintf( szBuf, websGetVar(wp, T("pathname"), T("0")) );
    if (strcmp(szBuf, "sys_info.asp") == 0) {
        if ( bChangedName ) {
            pageReload_sysinfoEx(wp, path, query);
            return;
        }
        pageReload_sysinfo(wp, path, query);
        return;
    }
    pageReload_dec01(wp, path, query);
}

void CWebSvr::formDevState(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    pageReload_state(wp, path, query);
}
void* CWebSvr::wait_thread(void * param)
{
    CFacility::SleepMsec(2000);
    exit(0);
    return NULL;
}
void CWebSvr::formDevSetting(webs_t wp, char_t *path, char_t *query)
{
	UpdateLastOpTime(wp);
	//
	char szBuf[64]={0};
	sprintf( szBuf, websGetVar(wp, T("submit_dev_model"), T("0")) );
	//printf("#############%s\n", szBuf);
	int iModel = atoi(szBuf);
	long lRet = g_pDWConfig->SetDeviceModel(iModel);
	if (lRet == 0) {
		//重启设备
		//formDevReboot(wp, path, query);
        pageReload_wait(wp, path, query);

        //重启服务
        pthread_t  waitThread;
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
        pthread_create(&waitThread, &attr, wait_thread, NULL);
		return;
	}

	pageReload_setting(wp, path, query);
}
void CWebSvr::formRestartSvr(webs_t wp, char_t *path, char_t *query)
{
	UpdateLastOpTime(wp);
	//重启设备
	//formDevReboot(wp, path, query);
    pageReload_wait(wp, path, query);
	
    //重启服务
    pthread_t  waitThread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    pthread_create(&waitThread, &attr, wait_thread, NULL);
	return;
}
void CWebSvr::formDevReset(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    //
    long lRet = g_pDWConfig->ResetParam();
    if (lRet == 0) {
        //重启设备
        formDevReboot(wp, path, query);
        return;
    }
    //重设失败
    pageReload_reset(wp, path, query);
}

void* CWebSvr::reboot_thread(void * param)
{
    CFacility::SleepMsec(3000);
    g_pDWConfig->RebootDevice();
    return NULL;
}

void CWebSvr::formDevReboot(webs_t wp, char_t *path, char_t *query)
{
    pageReload_rebooting(wp, path, query);
    pthread_t  RebootThread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    pthread_create(&RebootThread, &attr, reboot_thread, NULL);
}

void CWebSvr::formDevUpdate(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    char* ptrData  = wp->postData;
    int   iLenData = wp->lenPostData;
    long lRet = 0;
    if ( iLenData <= 0 ) {
        //printf("upload update file length: %d, error!\n", iLenData);
        pageReload_update(wp, path, query);
        m_iUpgradeRet = 2;
        return;
    }

    if ( ptrData != NULL && ptrData[0] != '\0' ) {
        lRet = g_pDWConfig->UpgradeDevice(ptrData, (unsigned long)iLenData);
        if ( lRet != RET_SUCCESS ) {
            m_iUpgradeRet = 2;
        }
        else{
            m_iUpgradeRet = 1;
        }
    }
    pageReload_update(wp, path, query);
}

void CWebSvr::formDecSetChannel(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[256]={0};
    struDecChannelInfo sObj;
    CProfile pro;
    int iChannelCount = 0;    
    // 从配置文件中获取通道个数
    if (pro.load(CFG_FILE_DECODER) < 0)
    {
        printf("load file failed [FileName=%s]\n", CFG_FILE_DECODER);
        return;
    }
    iChannelCount = pro.GetProperty("COUNT", "DecChannelCount", 0);
    if (iChannelCount<=0 ) {
        printf("channel error! [count=%d]\n", iChannelCount);
    }
    
    memset(&sObj, 0, sizeof(struDecChannelInfo));
    sprintf( szBuf, websGetVar(wp, T("chn_NO"), T("0")) );
    sObj.channel = atoi(szBuf);
    sprintf( szBuf, websGetVar(wp, T("chn_CODE"), T("0")) );
    sprintf(sObj.code, "%s", szBuf);
    lRet = g_pDWConfig->SetDecChannelInfo(&sObj);
    pageReload_channelset(wp, path, query);
}

void CWebSvr::formDecSetResolution(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[64] = {0};
    struDisplayResolution sDR; 

    memset(&sDR, 0, sizeof(struDisplayResolution));

    sprintf( szBuf, websGetVar(wp, T("resolution"), T("0")) );
    sDR.resolution = atoi(szBuf);

    sprintf( szBuf, websGetVar(wp, T("channel"), T("0")) );
    sDR.channel = atoi(szBuf);
    
    sprintf( szBuf, websGetVar(wp, T("displaymode"), T("0")) );
    sDR.displaymode = atoi(szBuf);

    sprintf( szBuf, websGetVar(wp, T("displayno"), T("0")) );
    sDR.displayno = atoi(szBuf);

    lRet = g_pDWConfig->SetResolution(&sDR);

    pageReload_resolution(wp, path, query);
}

void CWebSvr::formDecSetChnDynamic(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[256]={0};
    struDynamicDecUrl sDDU;
    CProfile pro;
    int iChannelCount = 0;    
    // 从配置文件中获取通道个数
    if (pro.load(CFG_FILE_DECODER) < 0)
    {
        printf("load file failed [FileName=%s]\n", CFG_FILE_DECODER);
        return;
    }
    iChannelCount = pro.GetProperty("COUNT", "DecChannelCount", 0);
    if (iChannelCount<=0 ) {
        printf("channel error! [count=%d]\n", iChannelCount);
    }
    
    memset(&sDDU, 0, sizeof(struDynamicDecUrl));
    sprintf( szBuf, websGetVar(wp, T("chn_NO"), T("0")) );
    sDDU.channel = atoi(szBuf);
    sprintf( szBuf, websGetVar(wp, T("chn_URL"), T("0")) );
    sprintf(sDDU.url, "%s", szBuf);
    sprintf( szBuf, websGetVar(wp, T("chn_FPS"), T("0")) );
    sDDU.fps = atoi(szBuf);
    lRet = g_pDWConfig->SetDynamicDecUrl(&sDDU);

    pageReload_dynamic(wp, path, query);
}

void CWebSvr::formEditUserInfo(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    struUserInfo objUI;
    char szBuf[64]={0};
    memset(&objUI, 0, sizeof(struUserInfo));
    sprintf( objUI.name, websGetVar(wp, T("username"), T("0")) );
    sprintf( objUI.pass, websGetVar(wp, T("userpass"), T("0")) );
    sprintf( szBuf, websGetVar(wp, T("usertype"), T("0")) );
    objUI.flag = atoi(szBuf);
    lRet = g_pDWConfig->EditUserInfo(&objUI);
    if (lRet < 0) {
        printf("Edit User Info failed!\n");
    }
    pageReload_user(wp, path, query);
}

void CWebSvr::formEncDisplay(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[1024] = {0};
    sprintf( szBuf, websGetVar(wp, T("submit_str"), T("0")) );
    //printf("###Display: submit_str = \"%s\"\n", szBuf);
    lRet = g_pEWConfig->SetEncDisplay(szBuf);
    pageReload_display(wp, path, query);
}
void CWebSvr::formEncTransfer(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[1024] = {0};
    sprintf( szBuf, websGetVar(wp, T("submit_str"), T("0")) );
    //printf("###Transfer: submit_str = \"%s\"\n", szBuf);
    lRet = g_pEWConfig->SetEncTransfer(szBuf);
    pageReload_transfer(wp, path, query);
}
void CWebSvr::formEncVideo(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[1024] = {0};
    sprintf( szBuf, websGetVar(wp, T("submit_str"), T("0")) );
    //printf("###Video: submit_str = \"%s\"\n", szBuf);
    lRet = g_pEWConfig->SetEncVideo(szBuf);
    pageReload_video(wp, path, query);
}

void CWebSvr::formEncAlarm(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[1024] = {0};
    sprintf( szBuf, websGetVar(wp, T("submit_str"), T("0")) );
    printf("###Alarm: submit_str = \"%s\"\n", szBuf);
    lRet = g_pEWConfig->SetEncAlarm(szBuf);
    pageReload_alarm(wp, path, query);
}

void CWebSvr::formEncChannel(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[1024] = {0};
    sprintf( szBuf, websGetVar(wp, T("submit_str"), T("0")) );
    //printf("###Channel: submit_str = \"%s\"\n", szBuf);
    lRet = g_pEWConfig->SetEncChannel(szBuf);
    pageReload_channel(wp, path, query);
}
void CWebSvr::formEncPtzPort(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[1024] = {0};
    sprintf( szBuf, websGetVar(wp, T("submit_ptzport_str"), T("0")) );
    //printf("###PtzPort: submit_ptzport_str = \"%s\"\n", szBuf);
    lRet = g_pEWConfig->SetEncPtzPort(szBuf);
    pageReload_channel(wp, path, query);
}
void CWebSvr::formEncForwardport(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[1024] = {0};
    sprintf( szBuf, websGetVar(wp, T("submit_forwardport_str"), T("0")) );
    //printf("###Forward Port: submit_forwardport_str = \"%s\"\n", szBuf);
    lRet = g_pEWConfig->SetEncForwardport(szBuf);
    pageReload_channel(wp, path, query);
}
void CWebSvr::formDecOsd(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[1024] = {0};
    struDecOsdInfo osd;
    memset(&osd, 0, sizeof(struDecOsdInfo));
    int info_show = 0;
    int mid_show = 0;
    g_pDWConfig->GetDecOsdShow(&osd);
    sprintf( szBuf, websGetVar(wp, T("osd_showed"), T("0")) );
    info_show = atoi(szBuf);
    sprintf( szBuf, websGetVar(wp, T("osd_mid_showed"), T("0")) );
    mid_show = atoi(szBuf);
    osd.show = 0;
    if (info_show == 1) // OSD INFO
    {
        osd.show += 1;
    }
    if (mid_show == 1) //显示监视器ID
    {
        osd.show += 2;
    }
    lRet = g_pDWConfig->SetDecOsdShow(&osd);
    pageReload_resolution(wp, path, query);
}

void CWebSvr::formPing(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    long lRet = 0;
    char szIp[80] = {0};
    char szCmd[100] = {0};
    sprintf(szIp, websGetVar(wp, T("host_ip"), T("")) );
    if( CFacility::bIpAddress(szIp) )
    {
        sprintf(szCmd, "ping -c 3 -w 3 %s > /tmp/ping.log", szIp);
        //printf("####\n%s\n####\n", szCmd);
        system(szCmd);
    }
    pageReload_ping(wp, path, query);
}

//设置自动重启信息
void CWebSvr::fromAutoReboot(webs_t wp, char_t *path, char_t *query)
{
    UpdateLastOpTime(wp);
    char szBuf[200] = {0};
    sprintf( szBuf, websGetVar(wp, T("submit_ar_str"), T("0")) );
    g_pDWConfig->SetAR(szBuf);
    pageReload_reboot(wp, path, query);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// asp
int CWebSvr::aspWebCheckUser(int eid, webs_t wp, int argc, char_t **argv)
{
    UpdateLastOpTime(wp);
    bool bChecked = false;
    char* ipaddr;
    ipaddr = websGetRequestIpaddr(wp);
    
    for(unsigned int i=0;i<MAX_USER;i++)
    {
        if (strcmp(g_userLocation[i].ip, ipaddr) == 0)
        {
            if ( g_userLocation[i].flag >= 0 ) 
            {
                bChecked = true;
                break;
            }            
        }
    }
    if ( ! bChecked ) 
    {
        websWrite(wp, T("<SCRIPT language=javascript>\n"));
        websWrite(wp, T("function browserRedirect() {"));
        websWrite(wp, T("top.window.location = \"http://%s\";}\n"), g_szIp);
        websWrite(wp, T("browserRedirect();</SCRIPT>"));
    }
    return 0;
}

int CWebSvr::aspCleanConnect(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    char *ipaddr;
    
    ipaddr = websGetRequestIpaddr(wp);
    
    for(unsigned int i=0; i<MAX_USER;i++)
    {
        if(strcmp(g_userLocation[i].ip, ipaddr) == 0)
        {
            strcpy(g_userLocation[i].ip, "\0");
            g_userLocation[i].flag = -1;
            strcpy(g_userLocation[i].user, "\0");
            break;
        }	
    }	
    return websWrite(wp, T("%d"), 0);
}

int CWebSvr::aspGetIpaddr(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    char buf[32] = {0};
    struNetworkInfo objNI;
    memset(&objNI, 0, sizeof(struNetworkInfo));
    long lRet = 0;

    lRet = g_pDWConfig->GetNetworkInfo(&objNI);
    if ( lRet != RET_SUCCESS) 
    {
        sprintf(buf, "%s", STR_FAILED);
    }
    else
    {
        sprintf(buf, "%s", objNI.ip);
    }
    return websWrite(wp, T("%s"), buf);
}

int CWebSvr::aspGetNetmask(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    char buf[32] = {0};
    struNetworkInfo objNI;
    memset(&objNI, 0, sizeof(struNetworkInfo));
    long lRet = 0;
    
    lRet = g_pDWConfig->GetNetworkInfo(&objNI);
    if ( lRet != RET_SUCCESS) 
    {
        sprintf(buf, "%s", STR_FAILED);
    }
    else
    {
        sprintf(buf, "%s", objNI.netmask);
    }
    return websWrite(wp, T("%s"), buf);
}

int CWebSvr::aspGetGateway(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    char buf[32] = {0};
    struNetworkInfo objNI;
    memset(&objNI, 0, sizeof(struNetworkInfo));
    long lRet = 0;
    
    lRet = g_pDWConfig->GetNetworkInfo(&objNI);
    if ( lRet != RET_SUCCESS) 
    {
        sprintf(buf, "%s", STR_FAILED);
    }
    else
    {
        sprintf(buf, "%s", objNI.gateway);
    }
    return websWrite(wp, T("%s"), buf);
}
int CWebSvr::aspGetSipServer(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    char szBuf[256] = {0};
    struSipServer objSS;
    memset(&objSS, 0, sizeof(struSipServer));
    g_pDWConfig->GetSipServer(&objSS);
    sprintf(szBuf, "%s;%s;", objSS.ip, objSS.id);
    return websWrite(wp, T("%s"), szBuf);
}
int CWebSvr::aspGetUser(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    char buf[32] = {0};
    char *ipaddr = NULL;
    
    ipaddr = websGetRequestIpaddr(wp);    
    for(unsigned int i=0; i<MAX_USER;i++)
    {
        if(strcmp(g_userLocation[i].ip, ipaddr) == 0)
        {
            sprintf(buf, "%s", g_userLocation[i].user);
        }	
    }

    return websWrite(wp, T("%s"), buf);
}

int CWebSvr::aspGetHostname(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[64] = {0};
    char szValue[64] = {0};
    
    lRet = g_pDWConfig->GetHostname(szValue);
    if ( lRet != RET_SUCCESS ) 
    {
        sprintf(szBuf, "%s", STR_FAILED);
    }
    else
    {
        sprintf(szBuf, "%s", szValue);
    }
    
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetDevMAC(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[64] = {0};
    char szValue[64] = {0};

    lRet = g_pDWConfig->GetDeviceMAC(szValue);
    if ( lRet != RET_SUCCESS ) 
    {
        sprintf(szBuf, "%s", STR_FAILED);
    }
    else
    {
        sprintf(szBuf, "%s", szValue);
    }
    
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetDevModel(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[64] = {0};
    int iValue = 0;

    lRet = g_pDWConfig->GetDeviceModel(iValue);
	if (lRet == RET_SUCCESS && iValue < DEV_MODEL_CNT && iValue >= 0)
	{
		//sprintf(szBuf, "%s", DEV_MODELS[iValue]);
		sprintf(szBuf, "%d", iValue);
	}
	else
	{
		sprintf(szBuf, "%s", STR_FAILED);
	}
    
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetDevSN(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[64] = {0};
    char szValue[64] = {0};
    
    lRet = g_pDWConfig->GetDeviceSN(szValue);
    if ( lRet != RET_SUCCESS ) 
    {
        sprintf(szBuf, "%s", STR_FAILED);
    }
    else
    {
        sprintf(szBuf, "%s", szValue);
    }
    
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetDevVer(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[64] = {0};
    char szValue[64] = {0};
    
    lRet = g_pDWConfig->GetDeviceVer(szValue);
    if ( lRet != RET_SUCCESS ) 
    {
        sprintf(szBuf, "%s", STR_FAILED);
    }
    else
    {
        sprintf(szBuf, "%s", szValue);
    }
    
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetDevBuildtime(int eid, webs_t wp, int argc, char_t **argv)
{
    long lRet = 0;
    char szBuf[64] = {0};
    char szValue[64] = {0};
    
    lRet = g_pDWConfig->GetDevBuildtime(szValue);
    if ( lRet != RET_SUCCESS ) 
    {
        sprintf(szBuf, "%s", STR_FAILED);
    }
    else
    {
        sprintf(szBuf, "%s", szValue);
    }
    
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetTime(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[64] = {0};
    char szValue[64] = {0};
    
    lRet = g_pDWConfig->GetTime(szValue);
    if ( lRet != RET_SUCCESS ) 
    {
        sprintf(szBuf, "%s", STR_FAILED);
    }
    else
    {
        sprintf(szBuf, "%s", szValue);
    }
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetNtp(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[200] = {0};
    char szValue[200] = {0};
    
    lRet = g_pDWConfig->GetNtp(szValue);
    if ( lRet != RET_SUCCESS ) 
    {
        sprintf(szBuf, "%s", STR_FAILED);
    }
    else
    {
        sprintf(szBuf, "%s", szValue);
    }
    return websWrite(wp, T("%s"), szBuf);
}
int CWebSvr::aspGetUptime(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[64] = {0};
    char szValue[64] = {0};
    
    lRet = g_pDWConfig->GetDeviceUptime(szValue);
    if ( lRet != RET_SUCCESS ) 
    {
        sprintf(szBuf, "%s", "0");
    }
    else
    {
        sprintf(szBuf, "%s", szValue);
    }
    
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetUpgradeRet(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    char szBuf[64] = {0};
    
    if ( m_iUpgradeRet == 2 ) 
    {
        sprintf(szBuf, "%s", "升级失败！");
    }
    else if( m_iUpgradeRet == 1 )
    {
        sprintf(szBuf, "%s", "升级成功，请重启设备生效");
    }
    else
    {
        sprintf(szBuf, "%s", " ");
    }
    m_iUpgradeRet = 0;
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetNetworkRet(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    char szBuf[64] = {0};
    
    if ( m_iNetworkRet == 2 ) 
    {
        sprintf(szBuf, "%s", "设置失败！");
    }
    else if( m_iNetworkRet == 1 )
    {
        sprintf(szBuf, "%s", "设置成功");
    }
    else
    {
        sprintf(szBuf, "%s", " ");
    }
    m_iNetworkRet = 0;
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetSysinfoRet(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    char szBuf[64] = {0};
    
    if ( m_iSysinfoRet == 2 ) 
    {
        sprintf(szBuf, "%s", "设置失败！");
    }
    else if( m_iSysinfoRet == 1 )
    {
        sprintf(szBuf, "%s", "设置成功");
    }
    else
    {
        sprintf(szBuf, "%s", " ");
    }
    m_iSysinfoRet = 0;
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetResolution(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    // 关联的asp函数需要1个参数，指示显示模式，如VGA/BNC等
    int iDisplaymode = atoi(argv[0]);
    struDisplayResolution sDR;
    int iDisplayChnCount = 0;
    CProfile pro;
    int iChannelCount = 0;
    char szBuf[400] = {0};
    char szTmp[32] = {0};
    int iLen = 0;
    if (pro.load(CFG_FILE_DECODER) < 0)
    {
        printf("load file failed [FileName=%s]\n", CFG_FILE_DECODER);
        return -1;
    }
    iChannelCount = pro.GetProperty("COUNT", "DecChannelCount", 0);

    switch(iDisplaymode)
    {
    case 1:// VGA
        iDisplayChnCount = pro.GetProperty("COUNT", "VgaChannelCount", 0);
        break;
    case 2:// BNC
        iDisplayChnCount = pro.GetProperty("COUNT", "BncChannelCount", 0);
        break;
    case 3:// HDMI
        iDisplayChnCount = pro.GetProperty("COUNT", "HdmiChannelCount", 0);
        break;
    default:
        printf("Invalid display mode[%d]", iDisplaymode);
        return -1;
    };    
    
    memset(&sDR, 0, sizeof(struDisplayResolution));
    sDR.displaymode = iDisplaymode;
    for(int i=0; i<iDisplayChnCount; i++)
    {
        sDR.displayno = i+1;
        lRet = g_pDWConfig->GetResolution(&sDR);
        if (lRet==0) 
        {
            sprintf(szTmp, "%d,", sDR.resolution);
            strcat(szBuf, szTmp);
        }
        else
        {
            return websWrite(wp, T("%s"), "0");
        }
    }
    // 去掉最后一个“,”
    iLen = strlen(szBuf);
    szBuf[iLen-1] = '\0';
    return websWrite(wp, T("%s"), szBuf);
}
int CWebSvr::aspGetResolutionChn(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    // 返回显示通道关联的通道号1开始，0表示未关联
    long lRet = 0;
    // 关联的asp函数需要1个参数，指示显示模式，如VGA/BNC等
    int iDisplaymode = atoi(argv[0]);
    struDisplayResolution sDR;
    int iDisplayChnCount = 0;
    CProfile pro;
    int iChannelCount = 0;
    char szBuf[400] = {0};
    char szTmp[32] = {0};
    int iLen = 0;
    if (pro.load(CFG_FILE_DECODER) < 0)
    {
        printf("load file failed [FileName=%s]\n", CFG_FILE_DECODER);
        return -1;
    }
    iChannelCount = pro.GetProperty("COUNT", "DecChannelCount", 0);
    
    switch(iDisplaymode)
    {
    case 1:// VGA
        iDisplayChnCount = pro.GetProperty("COUNT", "VgaChannelCount", 0);
        break;
    case 2:// BNC
        iDisplayChnCount = pro.GetProperty("COUNT", "BncChannelCount", 0);
        break;
    case 3:// HDMI
        iDisplayChnCount = pro.GetProperty("COUNT", "HdmiChannelCount", 0);
        break;
    default:
        printf("Invalid display mode[%d]", iDisplaymode);
        return -1;
    };    
    
    memset(&sDR, 0, sizeof(struDisplayResolution));
    sDR.displaymode = iDisplaymode;
    for(int i=0; i<iDisplayChnCount; i++)
    {
        sDR.displayno = i+1;
        lRet = g_pDWConfig->GetResolution(&sDR);
        if (lRet==0) 
        {
            sprintf(szTmp, "%d,", sDR.channel);
            strcat(szBuf, szTmp);
        }
        else
        {
            return websWrite(wp, T("%s"), "0");
        }
    }
    // 去掉最后一个“,”
    iLen = strlen(szBuf);
    szBuf[iLen-1] = '\0';
    return websWrite(wp, T("%s"), szBuf);
}

int CWebSvr::aspGetChnDynamic(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    int iChn = atoi(argv[0]);
    struDynamicDecUrl sDDU;
    CProfile pro;
    int iChannelCount = 0;    
    // 从配置文件中获取通道个数
    if (pro.load(CFG_FILE_DECODER) < 0)
    {
        printf("load file failed [FileName=%s]\n", CFG_FILE_DECODER);
        return -1;
    }
    
    //iChannelCount = pro.GetProperty("COUNT", "DecChannelCount", 0);
    g_pDWConfig->GetChannelCount(CHN_DECODER, iChannelCount);
    if (iChannelCount<=0 || iChn>iChannelCount) {
        printf("channel error! [count=%d, no=%d]\n", iChannelCount, iChn);
    }
    
    
    memset(&sDDU, 0, sizeof(struDynamicDecUrl));
    sDDU.channel = iChn;
    lRet = g_pDWConfig->GetDynamicDecUrl(&sDDU);
    if ( lRet == 0) {
        return websWrite(wp, T("%s"), sDDU.url);
    }
    
    return websWrite(wp, T("%s"), "");
}

int CWebSvr::aspGetChnCode(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    int iChn = atoi(argv[0]);
    CProfile pro;
    int iChannelCount = 0;    
    // 从配置文件中获取通道个数
    if (pro.load(CFG_FILE_DECODER) < 0)
    {
        printf("load file failed [FileName=%s]\n", CFG_FILE_DECODER);
        return -1;
    }
    
    //iChannelCount = pro.GetProperty("COUNT", "DecChannelCount", 0);
    g_pDWConfig->GetChannelCount(CHN_DECODER, iChannelCount);
    if (iChannelCount<=0 || iChn>iChannelCount) {
        printf("channel error! [count=%d, no=%d]\n", iChannelCount, iChn);
    }
	struDecChannelInfo sDCI;
	memset(&sDCI, 0, sizeof(struDecChannelInfo));
	sDCI.channel = iChn;
	lRet = g_pDWConfig->GetDecChannelInfo(&sDCI);
    if ( lRet == 0) {
        return websWrite(wp, T("%s"), sDCI.code);
    }
    return websWrite(wp, T("%s"), "0");
}
int CWebSvr::aspGetChnFps(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    int iChn = atoi(argv[0]);
    struDynamicDecUrl sDDU;
    CProfile pro;
    int iChannelCount = 0;    
    // 从配置文件中获取通道个数
    if (pro.load(CFG_FILE_DECODER) < 0)
    {
        printf("load file failed [FileName=%s]\n", CFG_FILE_DECODER);
        return -1;
    }
    
    //iChannelCount = pro.GetProperty("COUNT", "DecChannelCount", 0);
    g_pDWConfig->GetChannelCount(CHN_DECODER, iChannelCount);
    if (iChannelCount<=0 || iChn>iChannelCount) {
        printf("channel error! [count=%d, no=%d]\n", iChannelCount, iChn);
    }
    
    memset(&sDDU, 0, sizeof(struDynamicDecUrl));
    sDDU.channel = iChn;
    lRet = g_pDWConfig->GetDynamicDecUrl(&sDDU);
    if ( lRet == 0) {
        return websWrite(wp, T("%d"), sDDU.fps);
    }
    
    return websWrite(wp, T("%s"), "");
}
int CWebSvr::aspGetUserList(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    struUserInfo* pUserInfo = NULL;
    int iUserCount = 0;
    char szBuf[1024] = {0};
    int iLen = 0;

    lRet = g_pDWConfig->GetUserInfo(pUserInfo, iUserCount);
    if (lRet < 0) {
        return websWrite(wp, T("%s"), "");
    }
    for(int i=0; i<iUserCount; i++)
    {
        sprintf(szBuf+iLen, "%s:%d;", pUserInfo[i].name, pUserInfo[i].flag);
        iLen = strlen(szBuf);
    }
    szBuf[iLen-1]='\0';
    if (pUserInfo!=NULL) {
        delete [] pUserInfo;
    }
    return websWrite(wp, T("%s"), szBuf);
}
int CWebSvr::aspGetEncDisplay(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[4096] = {0};
    // 编码通道，从1开始
    int iEncChnno = atoi(argv[0]);
    lRet = g_pEWConfig->GetEncDisplay(szBuf, iEncChnno);

    return websWrite(wp, T("%s"), szBuf);
}
int CWebSvr::aspGetEncTransfer(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[4096] = {0};
    // 编码通道，从1开始
    int iEncChnno = atoi(argv[0]);
    /*if (iEncChnno==1) {
        sprintf(szBuf, "");
    }
    else if (iEncChnno==2) {
        sprintf(szBuf, "");
    }*/
    lRet = g_pEWConfig->GetEncTransfer(szBuf, iEncChnno);

    return websWrite(wp, T("%s"), szBuf);
}
int CWebSvr::aspGetEncVideo(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[4096] = {0};
    // 编码通道，从1开始(1-表示通道1主码流，2-表示通道1子码流，3-表示通道2主码流，依次类推)
    int iEncChnno = atoi(argv[0]);
    lRet = g_pEWConfig->GetEncVideo(szBuf, iEncChnno);

    return websWrite(wp, T("%s"), szBuf);
}
int CWebSvr::aspGetEncChannel(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[4096] = {0};
    int iEncChnno = atoi(argv[0]);
    lRet = g_pEWConfig->GetEncChannel(szBuf, iEncChnno);

    return websWrite(wp, T("%s"), szBuf);
}
int CWebSvr::aspGetEncAlarmin(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[4096] = {0};
    int iNo = atoi(argv[0]);
    lRet = g_pEWConfig->GetEncAlarmin(szBuf, iNo);
    
    return websWrite(wp, T("%s"), szBuf);
}
int CWebSvr::aspGetEncAlarmout(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[4096] = {0};
    int iNo = atoi(argv[0]);
    lRet = g_pEWConfig->GetEncAlarmout(szBuf, iNo);
    
    return websWrite(wp, T("%s"), szBuf);
}
int CWebSvr::aspGetEncPtzPort(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[4096] = {0};
    lRet = g_pEWConfig->GetEncPtzPort(szBuf);
    
    return websWrite(wp, T("%s"), szBuf);
}
int CWebSvr::aspGetEncForwardPort(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[4096] = {0};
    lRet = g_pEWConfig->GetEncForwardport(szBuf);
    
    return websWrite(wp, T("%s"), szBuf);
}
// 获取通道个数
int CWebSvr::aspGetChannelCount(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    int iChannelMode = atoi(argv[0]);
    int iChannelCount = 0;
    
    //
    lRet = g_pDWConfig->GetChannelCount(iChannelMode, iChannelCount);
    if (lRet < 0) {
        return websWrite(wp, T("%d"), 0);
    }
    
    return websWrite(wp, T("%d"), iChannelCount);
}
int CWebSvr::aspGetDecOsdShow(int eid, webs_t wp, int argc, char_t **argv)
{
    long lRet = 0;
    struDecOsdInfo osd;
    memset(&osd, 0, sizeof(struDecOsdInfo));
    lRet = g_pDWConfig->GetDecOsdShow(&osd);
    if (lRet < 0) {
        return websWrite(wp, T("%d"), 0);
    }
    
    int info_show = 0;
    int mid_show = 0;
    if (osd.show & 1) // OSD INFO
    {
        info_show = 1;
    }
    if (osd.show & 2) //显示监视器ID
    {
        mid_show = 1;
    }

    return websWrite(wp, T("%d,%d"), info_show, mid_show);
}
int CWebSvr::aspGetPingRet(int eid, webs_t wp, int argc, char_t **argv)
{
    int iRet = 0;
    bool bPing = false;
    char *szBuf = NULL;
    unsigned long ulFilesize = 0;
    FILE* fp = fopen("/tmp/ping.log", "r");
    if( fp != NULL )
    {
        fseek(fp, 0L, SEEK_END);  
        ulFilesize = ftell(fp);  
        szBuf = new char[ulFilesize+1];
        if (szBuf == NULL) 
        {
            printf("allocate memory error!\n");
            exit(0);
        }
        fseek(fp, 0L, SEEK_SET); 
        fread(szBuf, 1, ulFilesize, fp);
        szBuf[ulFilesize] = '\0';
        fclose(fp);
        remove("/tmp/ping.log");
    }
    else
    {
        //printf("fopen [/tmp/ping.log] failed\n");
        return websWrite(wp, T("%s"), "");
    }
    //printf("########################\n%s\n########################\n", szBuf);
    websWrite(wp, T("%s"), szBuf);
    delete [] szBuf;
    szBuf = NULL;
    return 0;
}

// 获取自动重启设置信息
int CWebSvr::aspGetARInfo(int eid, webs_t wp, int argc, char_t **argv)
{
    //UpdateLastOpTime(wp);
    long lRet = 0;
    char szBuf[200] = {0};
    char szValue[200] = {0};
    
    lRet = g_pDWConfig->GetAR(szValue);
    if ( lRet != RET_SUCCESS ) 
    {
        sprintf(szBuf, "%s", STR_FAILED);
    }
    else
    {
        sprintf(szBuf, "%s", szValue);
    }
    return websWrite(wp, T("%s"), szBuf);
}

//////////////////////////////////////////////////////////////////////////
// 网页导航
void CWebSvr::pageReload_index(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}

void CWebSvr::pageReload_main(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/main.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}

// 跳转系统信息网页
void CWebSvr::pageReload_dec01(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/dec01.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
void CWebSvr::pageReload_sysinfo(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/sys_info.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
// 刷新top部分
void CWebSvr::pageReload_sysinfoEx(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/sys_info.asp?refreshtop=1\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
// 跳转网页管理网页
void CWebSvr::pageReload_network(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/sys_network.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
// 跳转时间配置网页
void CWebSvr::pageReload_time(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/sys_time.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
// 跳转设备管理网页
void CWebSvr::pageReload_setting(webs_t wp, char_t *path, char_t *query)
{
	get_ip(g_szIp);
	websHeader(wp);
	websWrite(wp, T("OK! Reloading...\n"));
	websWrite(wp, T("<SCRIPT language=javascript>\n"));
	websWrite(wp, T("function browserRedirect() {"));
	websWrite(wp, T("location = \"http://%s/dev_setting.asp\";}\n"), g_szIp);
	websWrite(wp, T("browserRedirect();</SCRIPT>"));
	websFooter(wp);
	websDone(wp, 200);
}
// 跳转ping测试网页
void CWebSvr::pageReload_ping(webs_t wp, char_t *path, char_t *query)
{
    char szPingIP[80]={0};
    sprintf(szPingIP, websGetVar(wp, T("host_ip"), T("")) );
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/dev_ping.asp?ping_ip=%s\";}\n"), g_szIp, szPingIP);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
// 跳转设备状态网页
void CWebSvr::pageReload_state(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/dev_state.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}

// 跳转参数重置网页
void CWebSvr::pageReload_reset(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/dev_reset.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}

// 跳转设备重启网页
void CWebSvr::pageReload_reboot(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/dev_reboot.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));

    websFooter(wp);
    websDone(wp, 200);
}
// 跳转等待网页
void CWebSvr::pageReload_wait(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/waiting.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    
    websFooter(wp);
    websDone(wp, 200);
}
// 跳转设备重启中网页
void CWebSvr::pageReload_rebooting(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("top.window.location.replace(\"/rebooting.asp\");\n"));
    websWrite(wp, T("browserRedirect();</SCRIPT>"));

    websFooter(wp);
    websDone(wp, 200);
}

// 跳转设备升级网页
void CWebSvr::pageReload_update(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/dev_update.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}

void CWebSvr::pageReload_channelset(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/dec_channelset.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}

void CWebSvr::pageReload_resolution(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/dec_resolution.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}

void CWebSvr::pageReload_dynamic(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/dec_dynamic.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}

void CWebSvr::pageReload_user(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/sys_user.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
void CWebSvr::pageReload_video(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/enc_video.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
void CWebSvr::pageReload_display(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/enc_display.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
void CWebSvr::pageReload_transfer(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/enc_transfer.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
// 跳转至用编码器报警设置网页
void CWebSvr::pageReload_alarm(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/enc_alarm.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
// 跳转至用编码器通道设置网页
void CWebSvr::pageReload_channel(webs_t wp, char_t *path, char_t *query)
{
    get_ip(g_szIp);
    websHeader(wp);
    websWrite(wp, T("OK! Reloading...\n"));
    websWrite(wp, T("<SCRIPT language=javascript>\n"));
    websWrite(wp, T("function browserRedirect() {"));
    websWrite(wp, T("location = \"http://%s/enc_channel.asp\";}\n"), g_szIp);
    websWrite(wp, T("browserRedirect();</SCRIPT>"));
    websFooter(wp);
    websDone(wp, 200);
}
//////////////////////////////////////////////////////////////////////////
int CWebSvr::UpdateLastOpTime(webs_t wp)
{
    char* ipaddr;
    ipaddr = websGetRequestIpaddr(wp);
    
    for(unsigned int i=0; i<MAX_USER; i++)
    {
        if (strcmp(g_userLocation[i].ip, ipaddr) == 0)
        {
            g_iLastOpTime[i] = time(NULL); 
        }
    }
    return 0;
}




