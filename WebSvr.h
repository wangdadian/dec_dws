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
    // 获取解码通道FPS
    static int aspGetChnFps(int eid, webs_t wp, int argc, char_t **argv);
	// 获取通道编号
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
    // 获取通道个数
    static int aspGetChannelCount(int eid, webs_t wp, int argc, char_t **argv);
    static int aspGetDecOsdShow(int eid, webs_t wp, int argc, char_t **argv);
    // 获取ping测试结果
    static int aspGetPingRet(int eid, webs_t wp, int argc, char_t **argv);
    
	//获取自动重启设置信息
	static int aspGetARInfo(int eid, webs_t wp, int argc, char_t **argv);


    //////////////////////////////////////////////////////////////////////////
    // 更新最后操作时间
    static int UpdateLastOpTime(webs_t wp);
    // 检查用户操作，长时间不操作退出
    static void * ThCheckUser(void * param);
    void CheckUser();
    //
    ///////////////////////////////////////////////////////////
    //加载页面
    ///////////////////////////////////////////////////////////
    //加载登陆界面
    static void pageReload_index(webs_t wp, char_t *path, char_t *query);
    // 登陆后的跳转界面
    static void pageReload_main(webs_t wp, char_t *path, char_t *query);
    // 跳转系统信息网页
    static void pageReload_sysinfo(webs_t wp, char_t *path, char_t *query);
    static void pageReload_sysinfoEx(webs_t wp, char_t *path, char_t *query);
    static void pageReload_dec01(webs_t wp, char_t *path, char_t *query);
    // 跳转网页管理网页
    static void pageReload_network(webs_t wp, char_t *path, char_t *query);
    // 跳转时间配置网页
    static void pageReload_time(webs_t wp, char_t *path, char_t *query);
	// 跳转设备管理网页
    static void pageReload_setting(webs_t wp, char_t *path, char_t *query);
    // 跳转ping测试网页
    static void pageReload_ping(webs_t wp, char_t *path, char_t *query);
    // 跳转设备状态网页
    static void pageReload_state(webs_t wp, char_t *path, char_t *query);
    // 跳转参数重置网页
    static void pageReload_reset(webs_t wp, char_t *path, char_t *query);
    // 跳转设备重启网页
    static void pageReload_reboot(webs_t wp, char_t *path, char_t *query);
    // 跳转设备重启中网页
    static void pageReload_rebooting(webs_t wp, char_t *path, char_t *query);
    // 跳转至等待网页
    static void pageReload_wait(webs_t wp, char_t *path, char_t *query);
    // 跳转设备升级网页
    static void pageReload_update(webs_t wp, char_t *path, char_t *query);
    // 跳转解码器分辨率设置网页
    static void pageReload_resolution(webs_t wp, char_t *path, char_t *query);    
	// 跳转解码器通道设置网页
    static void pageReload_channelset(webs_t wp, char_t *path, char_t *query);
    // 跳转解码器动态解码网页
    static void pageReload_dynamic(webs_t wp, char_t *path, char_t *query);
    // 跳转至用户管理网页
    static void pageReload_user(webs_t wp, char_t *path, char_t *query);
    // 跳转至用编码器显示设置网页
    static void pageReload_display(webs_t wp, char_t *path, char_t *query);
    // 跳转至用编码器视频设置网页
    static void pageReload_video(webs_t wp, char_t *path, char_t *query);
    // 跳转至用编码器连接客户端设置网页
    static void pageReload_transfer(webs_t wp, char_t *path, char_t *query);
    // 跳转至用编码器报警设置网页
    static void pageReload_alarm(webs_t wp, char_t *path, char_t *query);
    // 跳转至用编码器通道设置网页
    static void pageReload_channel(webs_t wp, char_t *path, char_t *query);

	static int websHomePageHandler(webs_t wp, char_t *urlPrefix, char_t *webDir,int arg, char_t *url, char_t *path, char_t *query);
	void defaultErrorHandler(int etype, char_t *msg);
	void defaultTraceHandler(int level, char_t *buf);

private:
    CDWConfig *m_pDWConfig;
    CEWConfig *m_pEWConfig;
    static int m_iUpgradeRet;// 升级是否成功，0输出空字符串，1-输出成功，2-输出失败
    static int m_iNetworkRet; //设置网络信息是否成功，结果同上
    static int m_iSysinfoRet;// 设置系统信息是否成功，结果同上
    // 检查用户操作线程
    pthread_t m_thCheckUser;
    bool m_bExitFlag;
};

#endif  


