#ifndef __DW_CONFIG_H__
#define __DW_CONFIG_H__

#include "define.h"
#include "Facility.h"
#include "dwstype.h"

#include "User.h"
#include "Network.h"
#include "SysInfo.h"
#include "TimeCfg.h"
#include "Device.h"
#include "WebDecoder.h"

// 回调函数类型
// 获取、设置网络参数
typedef long (*GetNetworkInfoCB_T)(struNetworkInfo* pNI, void* param);
typedef long (*SetNetworkInfoCB_T)(const struNetworkInfo* pNI, void* param);
// 获取、设置SIP服务器参数
typedef long (*GetSipServerCB_T)(struSipServer* pSS, void* param);
typedef long (*SetSipServerCB_T)(const char* szBuf, void* param);
// 升级回调
typedef long (*UpgradeDevCB_T)(const char* szData, unsigned long ulLen, void* param);
// 获取设置MAC
typedef long (*GetDeviceMacCB_T)(char* szMAC, void* param);
typedef long (*SetDeviceMacCB_T)(const char* szMAC, void* param);
// 获取、设置分辨率
typedef long (*GetResolutionCB_T)(struDisplayResolution* pDR, void* param);
typedef long (*SetResolutionCB_T)(const struDisplayResolution* pDR, void* param);
// 获取、设置动态解码URL
typedef long (*GetDynamicDecUrlCB_T)(struDynamicDecUrl* pDDU, void* param);
typedef long (*SetDynamicDecUrlCB_T)(const struDynamicDecUrl* pDDU, void* param);
// 获取、设置解码通道信息
typedef long (*GetDecChannelInfoCB_T)(struDecChannelInfo* pDCI, void* param);
typedef long (*SetDecChannelInfoCB_T)(const struDecChannelInfo* pDCI, void* param);
// 重设参数
typedef long (*SetResetParamCB_T)(int iType, void* param);
// 获取、设置主机名称
typedef long (*GetHostnameCB_T)(char* szHostname, void* param);
typedef long (*SetHostnameCB_T)(const char* szHostname, void* param);
// 用户登录及验证
typedef long (*UserLoginCB_T)(char* szUserName, char* szPassword, void* param);
//获取用户信息，密码填空
typedef long (*GetUserInfoCB_T)(struUserInfo* &pUserInfo, int &iUserCount, void* param);
// 修改用户信息
typedef long (*EditUserInfoCB_T)(const struUserInfo* pUserInfo, void* param);
// 获取、设置设备型号
typedef long (*GetDeviceModelCB_T)(int& iModel, void* param);
typedef long (*SetDeviceModelCB_T)(int iModel, void* param);
// 获取设备序列号
typedef long (*GetDeviceSNCB_T)(char* szSN, void* param);
// 设置设备序列号
typedef long (*SetDeviceSNCB_T)(const char* szSN, void* param);
// 获取设备主控软件版本号
typedef long (*GetDeviceVerCB_T)(char* szVer, void* param);
// 获取系统最后更新时间
typedef long (*GetDevBuildtimeCB_T)(char* szTime, void* param);
// 设置、获取系统时间
typedef long (*SetSysTimeCB_T)(const char* szTime, void* param);
typedef long (*GetSysTimeCB_T)(char* szTime, void* param);
// 获取、设置NTP校时
typedef long (*GetNtpCB_T)(char* szBuf, void* param);
typedef long (*SetNtpCB_T)(const char* szBuf, void* param);
// 获取通道个数
typedef long (*GetChannelCountCB_T)(int iMode, int& iCount, void* param);

// 获取/设置OSD显示
typedef long (*DecOsdShowCB_T)(struDecOsdInfo* posd, void* param);

// 获取、设置自动重启信息
typedef long (*GetARCB_T)(char* szBuf, void* param);
typedef long (*SetARCB_T)(const char* szBuf, void* param);

class CDWConfig
{
public:
	CDWConfig();
	~CDWConfig();

    //////////////////////////////////////////////////////////////////////////
    // 用户
    // 用户登录及验证
    long UserLogin(char* szUserName, char* szPassword);
    //获取用户信息，密码填空
    long GetUserInfo(struUserInfo* &pUserInfo, int &iUserCount);
    // 修改用户信息
    long EditUserInfo(const struUserInfo* pUserInfo);
    //////////////////////////////////////////////////////////////////////////
    // 获取通道个数
    long GetChannelCount(int iMode, int &iCount);

    //////////////////////////////////////////////////////////////////////////
    // 网络
    // 获取网络信息
    long GetNetworkInfo(struNetworkInfo* pNI);
    // 设置网络信息
    long SetNetworkInfo(const struNetworkInfo* pNI);
    
    // SIP服务器
    // 获取、设置SIP服务器信息
    long GetSipServer(struSipServer* pSS);
    long SetSipServer(const char* szBuf);

    long GetDecOsdShow(struDecOsdInfo* posd);
    long SetDecOsdShow(struDecOsdInfo* posd);

    //////////////////////////////////////////////////////////////////////////
    // 系统信息 
    // 获取MAC
    // szMAC: 调用者分配64字节空间内存
    long GetDeviceMAC(char* szMAC);

    // 设置MAC
    long SetDeviceMAC(const char* szMAC);
    
    // 获取设备型号
    long GetDeviceModel(int& iModel);
	long SetDeviceModel(int iModel);
    
    // 获取设备序列号
    // szSN：调用者分配64字节内存
    long GetDeviceSN(char* szSN);
    // 设置设备序列号
    long SetDeviceSN(const char* szSN);
    
    // 获取设备主控软件版本号
    // szVer：调用者分配64字节内存
    long GetDeviceVer(char* szVer);

    // 获取系统最后创建时间
    // szTime：调用者分配64字节内存
    long GetDevBuildtime(char* szTime);

    //////////////////////////////////////////////////////////////////////////
    // 时间
    // 获取当前时间，时间格式：2013-10-10 10:10:10
    // szTime: 调用者分配64字节内存
    long GetTime(char* szTime);
    
    // 设置时间，时间格式：2013-10-10 10:10:10
    long SetTime(const char* szTime);
    // 获取、设置NTp
    long GetNtp(char* szBuf);
    long SetNtp(const char* szBuf);

    // 设备维护
    // 获取设备运行时间
    // szUptime：调用者申请64字节内存
    long GetDeviceUptime(char* szUptime);
    
    // 获取设置主机名称, szHostname-64字节字符串
    long GetHostname(char* szHostname);
    long SetHostname(const char* szHostname);

    // 重设设备参数，1-全部重设，2-局部重设
    long ResetParam(int iType=1);
    
    // 重启设备
    long RebootDevice();
    
    // 升级设备
    long UpgradeDevice(const char* szData, unsigned long ulLen);

	// 获取、设置解码通道信息
    long GetDecChannelInfo(struDecChannelInfo* pDCI);
    long SetDecChannelInfo(const struDecChannelInfo* pDCI);
    // 获取、设置分辨率
    long GetResolution(struDisplayResolution* pDR);
    long SetResolution(const struDisplayResolution* pDR);
    // 获取、设置动态解码URL
    long GetDynamicDecUrl(struDynamicDecUrl* pDDU);
    long SetDynamicDecUrl(const struDynamicDecUrl* pDDU);

	// 获取、设置自动重启信息
    long GetAR(char* szBuf);
    long SetAR(const char* szBuf);

    //////////////////////////////////////////////////////////////////////////
    // 用户登录及验证
    void SetCB_UserLogin(UserLoginCB_T cbFun, void* pCBobj=NULL);
    //获取用户信息，密码填空
    void SetCB_GetUserInfo(GetUserInfoCB_T cbFun, void* pCBobj=NULL);
    // 修改用户信息
    void SetCB_EditUserInfo(EditUserInfoCB_T cbFun, void* pCBobj=NULL);
    // 设置回调函数
    // 获取、设置网络参数
    void SetCB_GetNetworkInfo(GetNetworkInfoCB_T cbGetNI, void* pCBobj=NULL);
    void SetCB_SetNetworkInfo(SetNetworkInfoCB_T cbSetNI, void* pCBobj=NULL);
    void SetCB_GetSipServer(GetSipServerCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetSipServer(SetSipServerCB_T cbFun, void* pCBobj=NULL);
    void SetCB_UpgradeDev(UpgradeDevCB_T cbUD, void* pCBobj=NULL);
    void SetCB_GetDeviceMac(GetDeviceMacCB_T cbGetDM, void* pCBobj=NULL);
    void SetCB_SetDeviceMac(SetDeviceMacCB_T cbSetDM, void* pCBobj=NULL);
	// 获取、设置解码通道信息
    void SetCB_GetDecChannelInfo(GetDecChannelInfoCB_T cbGetDCI, void* pCBobj=NULL);
    void SetCB_SetDecChannelInfo(SetDecChannelInfoCB_T cbSetDCI, void* pCBobj=NULL);
    // 设置获取、设置分辨率回调
    void SetCB_GetResolution(GetResolutionCB_T cbGetRes, void* pCBobj=NULL);
    void SetCB_SetResolution(SetResolutionCB_T cbSetRes, void* pCBobj=NULL);
    // 获取、设置动态解码URL回调
    void SetCB_GetDynamicDecUrl(GetDynamicDecUrlCB_T cbGetDDU, void* pCBobj=NULL);
    void SetCB_SetDynamicDecUrl(SetDynamicDecUrlCB_T cbSetDDU, void* pCBobj=NULL);
    // 设置重设参数回调
    void SetCB_ResetParam(SetResetParamCB_T cbResetParam, void* pCBobj=NULL);
    // 获取、设置主机名回调
    void SetCB_GetHostname(GetHostnameCB_T cbGetHostname, void* pCBobj=NULL);
    void SetCB_SetHostname(SetHostnameCB_T cbSetHostname, void* pCBobj=NULL);
    // 获取设备型号回调
    void SetCB_GetDeviceModel(GetDeviceModelCB_T cbFun, void* pCBobj=NULL);
	void SetCB_SetDeviceModel(SetDeviceModelCB_T cbFun, void* pCBobj=NULL);
    // 设置/获取设备序列号回调
    void SetCB_GetDeviceSN(GetDeviceSNCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetDeviceSN(SetDeviceSNCB_T cbFun, void* pCBobj=NULL);
    // 获取设备主控软件版本号回调
    void SetCB_GetDeviceVer(GetDeviceVerCB_T cbFun, void* pCBobj=NULL);
    void SetCB_GetDevBuildtime(GetDevBuildtimeCB_T cbFun, void* pCBobj=NULL);
    // 设置系统时间回调
    void SetCB_SetSysTime(SetSysTimeCB_T cbFun, void* pCBobj=NULL);
    void SetCB_GetSysTime(GetSysTimeCB_T cbFun, void* pCBobj=NULL);    
    // 设置NTP服务器IP地址回调
    void SetCB_GetNtp(GetNtpCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetNtp(SetNtpCB_T cbFun, void* pCBobj=NULL);
    // 获取、设置OSD回调
    void SetCB_GetDecOsdShow(DecOsdShowCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetDecOsdShow(DecOsdShowCB_T cbFun, void* pCBobj=NULL);
    // 获取通道个数
    void SetCB_GetChannelCount(GetChannelCountCB_T cbFun, void* pCBobj=NULL);
	// 设置自动重启回调
    void SetCB_GetAR(GetARCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetAR(SetARCB_T cbFun, void* pCBobj=NULL);
private:
    // 转换字符串中的空格为html空格&nbsp;
    // szValue：转换后的字符串，空间由调用者处理
    long conv_space_html(const char* szStr, char* szValue);
    // 转换字符串中的html空格&nbsp为空格" ";
    // szValue：转换后的字符串，空间由调用者处理
    long conv_html_space(const char* szStr, char* szValue);

private:
    CUser *m_pUser;
    CNetwork *m_pNetwork;
    CSysInfo *m_pSysInfo;
    CTimeCfg *m_pTimeCfg;
    CDevice  *m_pDevice;
    CWebDecoder * m_pWebDecoder;
private:
    // 回调成员   
    static UserLoginCB_T m_cbUserLogin;
    static void* m_pobjUserLogin;
    static GetUserInfoCB_T m_cbGetUI;
    static void* m_pobjGetUI;
    static EditUserInfoCB_T m_cbEditUI;
    static void* m_pobjEditUI;

    static GetSipServerCB_T m_cbGetSipSvr;
    static void* m_pobjGetSipSvr;
    static SetSipServerCB_T m_cbSetSipSvr;
    static void* m_pobjSetSipSvr;

    static GetNetworkInfoCB_T m_cbGetNI;
    static void* m_pobjGetNI;
    static SetNetworkInfoCB_T m_cbSetNI;
    static void* m_pobjSetNI;

    static UpgradeDevCB_T m_cbUpgradeDev;
    static void* m_pobjUD;

    static GetDeviceMacCB_T m_cbGetDM;
    static void* m_pobjGetDM;
    static SetDeviceMacCB_T m_cbSetDM;
    static void* m_pobjSetDM;
    
    static GetDecChannelInfoCB_T m_cbGetDCI;
    static void* m_pobjGetDCI;    
    static SetDecChannelInfoCB_T m_cbSetDCI;
    static void* m_pobjSetDCI;

    static GetResolutionCB_T m_cbGetRes;
    static void* m_pobjGetRes;    
    static SetResolutionCB_T m_cbSetRes;
    static void* m_pobjSetRes;

    static GetDynamicDecUrlCB_T m_cbGetDDU;
    static void* m_pobjGetDDU;
    static SetDynamicDecUrlCB_T m_cbSetDDU;
    static void* m_pobjSetDDU;

    static GetHostnameCB_T m_cbGetHostname;
    static void* m_pobjGetHostname;
    static SetHostnameCB_T m_cbSetHostname;
    static void* m_pobjSetHostname;

    static DecOsdShowCB_T m_cbGetDecOsdShow;
    static void* m_pobjGetDecOsdShow;
    static DecOsdShowCB_T m_cbSetDecOsdShow;
    static void* m_pobjSetDecOsdShow;

    static SetResetParamCB_T m_cbResetParam;
    static void* m_pobjResetParam;

	static GetDeviceModelCB_T m_cbGetModel;
	static void* m_pobjGetModel;
	static SetDeviceModelCB_T m_cbSetModel;
	static void* m_pobjSetModel;
    static GetDeviceSNCB_T m_cbGetSN;
    static void* m_pobjGetSN;
    static SetDeviceSNCB_T m_cbSetSN;
    static void* m_pobjSetSN;    
    static GetDeviceVerCB_T m_cbGetVer;
    static void* m_pobjGetVer;
    static GetDevBuildtimeCB_T m_cbGetBT;
    static void* m_pobjGetBT;

    static SetSysTimeCB_T m_cbSetSysTime;
    static void* m_pobjSetSysTime;
    static GetSysTimeCB_T m_cbGetSysTime;
    static void* m_pobjGetSysTime;   
    static GetNtpCB_T m_cbGetNtp;
    static void* m_pobjGetNtp;
    static SetNtpCB_T m_cbSetNtp;
    static void* m_pobjSetNtp;

	static GetARCB_T m_cbGetAR;
    static void* m_pobjGetAR;
    static SetARCB_T m_cbSetAR;
    static void* m_pobjSetAR;

    static GetChannelCountCB_T m_cbGetChnCnt;
    static void* m_pobjGetChnCnt;
};


#endif	//__DW_CONFIG_H__


