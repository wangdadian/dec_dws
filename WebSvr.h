#ifndef WebSvr_H 

#define WebSvr_H 
extern "C"
{
    #include  <sys/ioctl.h>
    #include  <sys/stat.h>
    #include  <arpa/inet.h>
    #include  <fcntl.h>
    #include  <stdlib.h>
    #include  <string.h>
    #include  <stdio.h>
    #include    "goahead/uemf.h"
    #include	"goahead/wsIntrn.h"
    #include    "goahead/webs.h"
    #include  <signal.h>
    #include  <unistd.h> 
    #include  <sys/types.h>
    #include  <sys/wait.h>
    #include  <pthread.h>
    #include  <pwd.h>
    #include  <utime.h>
    #include  <termios.h>
    #include  <errno.h>
    #include  <netinet/in.h>
    #include  <sched.h>
    #include  <stdarg.h>
    #include  <time.h>
    #include  <getopt.h>
    #include  <sys/param.h>
    #include  <pwd.h>
    #include  <grp.h>
    #include  <linux/watchdog.h>
    #include  <arpa/inet.h>

    #include  <net/if.h>
    #include  <net/if_arp.h>
#ifdef WEBS_SSL_SUPPORT
    #include "goahead/websSSL.h"
#endif
    
#ifdef USER_MANAGEMENT_SUPPORT
    #include "goahead/um.h"
    void    formDefineUserMgmt(void);
#endif
};

#include "DWConfig.h"
#include "EWConfig.h"
#include "define.h"
#include "dwstype.h"
#include "IniFile.h"
//----------------------------------------------------------------------------
// WebSvr.h                                                                  
//----------------------------------------------------------------------------
char_t* websGetCgiCommName();
int websLaunchCgiProc(char_t *cgiPath, char_t **argp, char_t **envp,char_t *stdIn, char_t *stdOut);
int websCheckCgiProc(int handle);


class CWebSvr
{
public :    

	////    Constructors and destructors    ////
	CWebSvr();		//constructor
	~CWebSvr();	//destructor
    
	void init();    
	
	//## operation Timer_thread(void *) 
	static void * Http_thread(void * param);
    static void * reboot_thread(void * param);
    static void * wait_thread(void * param);
    //static void * upgrade_thread(void * param);
		
private:
	char_t		*rootWeb;			/* Root web directory */
	char_t		*password;				/* Security password */
	int			port;						/* Server port */
	int			retries ;					/* Server port retries */
	int			finished;						/* Finished flag */	

private:	
	int initWebs();
	int thttpd_start_main();
	static int reboot();
	static void get_ip(char *ip);
	
	static int	aspTest(int eid, webs_t wp, int argc, char_t **argv);
	static void formTest(webs_t wp, char_t *path, char_t *query);
    
    ///////////////////////////////////////////////////////////
    // form
    //
    static void formCheckUser(webs_t wp, char_t *path, char_t *query);
    static void formExitSystem(webs_t wp, char_t *path, char_t *query);
    static void formNetworkConfig(webs_t wp, char_t *path, char_t *query);
    static void formSetSipServer(webs_t wp, char_t *path, char_t *query);
    static void formSetTime(webs_t wp, char_t *path, char_t *query);
    static void formSetNtp(webs_t wp, char_t *path, char_t *query);
    static void formSetSysInfo(webs_t wp, char_t *path, char_t *query);
	static void formDevSetting(webs_t wp, char_t *path, char_t *query);
    static void formDevState(webs_t wp, char_t *path, char_t *query);
    static void formDevReset(webs_t wp, char_t *path, char_t *query);
    static void formDevReboot(webs_t wp, char_t *path, char_t *query);
    static void formDevUpdate(webs_t wp, char_t *path, char_t *query);
	static void formDecSetChannel(webs_t wp, char_t *path, char_t *query);
    static void formDecSetResolution(webs_t wp, char_t *path, char_t *query);
    static void formDecSetChnDynamic(webs_t wp, char_t *path, char_t *query);
    static void formEditUserInfo(webs_t wp, char_t *path, char_t *query);
    static void formEncDisplay(webs_t wp, char_t *path, char_t *query);
    static void formEncTransfer(webs_t wp, char_t *path, char_t *query);
    static void formEncVideo(webs_t wp, char_t *path, char_t *query);
    static void formEncAlarm(webs_t wp, char_t *path, char_t *query);
    static void formEncChannel(webs_t wp, char_t *path, char_t *query);
    static void formEncPtzPort(webs_t wp, char_t *path, char_t *query);
    static void formDecOsd(webs_t wp, char_t *path, char_t *query);
    static void formEncForwardport(webs_t wp, char_t *path, char_t *query);
    static void formPing(webs_t wp, char_t *path, char_t *query);
	static void formRestartSvr(webs_t wp, char_t *path, char_t *query);
	static void fromAutoReboot(webs_t wp, char_t *path, char_t *query);

    ///////////////////////////////////////////////////////////
    // asp
    //
    static int aspWebCheckUser(int eid, webs_t wp, int argc, char_t **argv);
    static int aspCleanConnect(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetIpaddr(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetNetmask(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetGateway(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetSipServer(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetUser(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetDevMAC(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetDevModel(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetDevSN(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetDevVer(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetDevBuildtime(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetTime(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetNtp(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetUptime(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetUpgradeRet(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetNetworkRet(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetSysinfoRet(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetResolution(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetResolutionChn(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetChnDynamic(int eid, webs_t wp, int argc, char_t **argv);
    // ��ȡ����ͨ��FPS
    static int aspGetChnFps(int eid, webs_t wp, int argc, char_t **argv);
	// ��ȡͨ�����
	static int aspGetChnCode(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetHostname(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetUserList(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetEncDisplay(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetEncTransfer(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetEncVideo(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetEncChannel(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetEncAlarmin(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetEncAlarmout(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetEncPtzPort(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetEncForwardPort(int eid, webs_t wp, int argc, char_t **argv);
    // ��ȡͨ������
    static int aspGetChannelCount(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetDecOsdShow(int eid, webs_t wp, int argc, char_t **argv);
    // ��ȡping���Խ��
    static int aspGetPingRet(int eid, webs_t wp, int argc, char_t **argv);
    
	//��ȡ�Զ�����������Ϣ
	static int aspGetARInfo(int eid, webs_t wp, int argc, char_t **argv);


    //////////////////////////////////////////////////////////////////////////
    // ����������ʱ��
    static int UpdateLastOpTime(webs_t wp);
    // ����û���������ʱ�䲻�����˳�
    static void * ThCheckUser(void * param);
    void CheckUser();
    //
    ///////////////////////////////////////////////////////////
    //����ҳ��
    ///////////////////////////////////////////////////////////
    //���ص�½����
    static void pageReload_index(webs_t wp, char_t *path, char_t *query);
    // ��½�����ת����
    static void pageReload_main(webs_t wp, char_t *path, char_t *query);
    // ��תϵͳ��Ϣ��ҳ
    static void pageReload_sysinfo(webs_t wp, char_t *path, char_t *query);
    static void pageReload_sysinfoEx(webs_t wp, char_t *path, char_t *query);
    static void pageReload_dec01(webs_t wp, char_t *path, char_t *query);
    // ��ת��ҳ������ҳ
    static void pageReload_network(webs_t wp, char_t *path, char_t *query);
    // ��תʱ��������ҳ
    static void pageReload_time(webs_t wp, char_t *path, char_t *query);
	// ��ת�豸������ҳ
    static void pageReload_setting(webs_t wp, char_t *path, char_t *query);
    // ��תping������ҳ
    static void pageReload_ping(webs_t wp, char_t *path, char_t *query);
    // ��ת�豸״̬��ҳ
    static void pageReload_state(webs_t wp, char_t *path, char_t *query);
    // ��ת����������ҳ
    static void pageReload_reset(webs_t wp, char_t *path, char_t *query);
    // ��ת�豸������ҳ
    static void pageReload_reboot(webs_t wp, char_t *path, char_t *query);
    // ��ת�豸��������ҳ
    static void pageReload_rebooting(webs_t wp, char_t *path, char_t *query);
    // ��ת���ȴ���ҳ
    static void pageReload_wait(webs_t wp, char_t *path, char_t *query);
    // ��ת�豸������ҳ
    static void pageReload_update(webs_t wp, char_t *path, char_t *query);
    // ��ת�������ֱ���������ҳ
    static void pageReload_resolution(webs_t wp, char_t *path, char_t *query);    
	// ��ת������ͨ��������ҳ
    static void pageReload_channelset(webs_t wp, char_t *path, char_t *query);
    // ��ת��������̬������ҳ
    static void pageReload_dynamic(webs_t wp, char_t *path, char_t *query);
    // ��ת���û�������ҳ
    static void pageReload_user(webs_t wp, char_t *path, char_t *query);
    // ��ת���ñ�������ʾ������ҳ
    static void pageReload_display(webs_t wp, char_t *path, char_t *query);
    // ��ת���ñ�������Ƶ������ҳ
    static void pageReload_video(webs_t wp, char_t *path, char_t *query);
    // ��ת���ñ��������ӿͻ���������ҳ
    static void pageReload_transfer(webs_t wp, char_t *path, char_t *query);
    // ��ת���ñ���������������ҳ
    static void pageReload_alarm(webs_t wp, char_t *path, char_t *query);
    // ��ת���ñ�����ͨ��������ҳ
    static void pageReload_channel(webs_t wp, char_t *path, char_t *query);

	static int websHomePageHandler(webs_t wp, char_t *urlPrefix, char_t *webDir,int arg, char_t *url, char_t *path, char_t *query);
	void defaultErrorHandler(int etype, char_t *msg);
	void defaultTraceHandler(int level, char_t *buf);

private:
    CDWConfig *m_pDWConfig;
    CEWConfig *m_pEWConfig;
    static int m_iUpgradeRet;// �����Ƿ�ɹ���0������ַ�����1-����ɹ���2-���ʧ��
    static int m_iNetworkRet; //����������Ϣ�Ƿ�ɹ������ͬ��
    static int m_iSysinfoRet;// ����ϵͳ��Ϣ�Ƿ�ɹ������ͬ��
    // ����û������߳�
    pthread_t m_thCheckUser;
    bool m_bExitFlag;
};

#endif  


