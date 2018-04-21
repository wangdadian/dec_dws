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

// �ص���������
// ��ȡ�������������
typedef long (*GetNetworkInfoCB_T)(struNetworkInfo* pNI, void* param);
typedef long (*SetNetworkInfoCB_T)(const struNetworkInfo* pNI, void* param);
// ��ȡ������SIP����������
typedef long (*GetSipServerCB_T)(struSipServer* pSS, void* param);
typedef long (*SetSipServerCB_T)(const char* szBuf, void* param);
// �����ص�
typedef long (*UpgradeDevCB_T)(const char* szData, unsigned long ulLen, void* param);
// ��ȡ����MAC
typedef long (*GetDeviceMacCB_T)(char* szMAC, void* param);
typedef long (*SetDeviceMacCB_T)(const char* szMAC, void* param);
// ��ȡ�����÷ֱ���
typedef long (*GetResolutionCB_T)(struDisplayResolution* pDR, void* param);
typedef long (*SetResolutionCB_T)(const struDisplayResolution* pDR, void* param);
// ��ȡ�����ö�̬����URL
typedef long (*GetDynamicDecUrlCB_T)(struDynamicDecUrl* pDDU, void* param);
typedef long (*SetDynamicDecUrlCB_T)(const struDynamicDecUrl* pDDU, void* param);
// ��ȡ�����ý���ͨ����Ϣ
typedef long (*GetDecChannelInfoCB_T)(struDecChannelInfo* pDCI, void* param);
typedef long (*SetDecChannelInfoCB_T)(const struDecChannelInfo* pDCI, void* param);
// �������
typedef long (*SetResetParamCB_T)(int iType, void* param);
// ��ȡ��������������
typedef long (*GetHostnameCB_T)(char* szHostname, void* param);
typedef long (*SetHostnameCB_T)(const char* szHostname, void* param);
// �û���¼����֤
typedef long (*UserLoginCB_T)(char* szUserName, char* szPassword, void* param);
//��ȡ�û���Ϣ���������
typedef long (*GetUserInfoCB_T)(struUserInfo* &pUserInfo, int &iUserCount, void* param);
// �޸��û���Ϣ
typedef long (*EditUserInfoCB_T)(const struUserInfo* pUserInfo, void* param);
// ��ȡ�������豸�ͺ�
typedef long (*GetDeviceModelCB_T)(int& iModel, void* param);
typedef long (*SetDeviceModelCB_T)(int iModel, void* param);
// ��ȡ�豸���к�
typedef long (*GetDeviceSNCB_T)(char* szSN, void* param);
// �����豸���к�
typedef long (*SetDeviceSNCB_T)(const char* szSN, void* param);
// ��ȡ�豸��������汾��
typedef long (*GetDeviceVerCB_T)(char* szVer, void* param);
// ��ȡϵͳ������ʱ��
typedef long (*GetDevBuildtimeCB_T)(char* szTime, void* param);
// ���á���ȡϵͳʱ��
typedef long (*SetSysTimeCB_T)(const char* szTime, void* param);
typedef long (*GetSysTimeCB_T)(char* szTime, void* param);
// ��ȡ������NTPУʱ
typedef long (*GetNtpCB_T)(char* szBuf, void* param);
typedef long (*SetNtpCB_T)(const char* szBuf, void* param);
// ��ȡͨ������
typedef long (*GetChannelCountCB_T)(int iMode, int& iCount, void* param);

// ��ȡ/����OSD��ʾ
typedef long (*DecOsdShowCB_T)(struDecOsdInfo* posd, void* param);

// ��ȡ�������Զ�������Ϣ
typedef long (*GetARCB_T)(char* szBuf, void* param);
typedef long (*SetARCB_T)(const char* szBuf, void* param);

class CDWConfig
{
public:
	CDWConfig();
	~CDWConfig();

    //////////////////////////////////////////////////////////////////////////
    // �û�
    // �û���¼����֤
    long UserLogin(char* szUserName, char* szPassword);
    //��ȡ�û���Ϣ���������
    long GetUserInfo(struUserInfo* &pUserInfo, int &iUserCount);
    // �޸��û���Ϣ
    long EditUserInfo(const struUserInfo* pUserInfo);
    //////////////////////////////////////////////////////////////////////////
    // ��ȡͨ������
    long GetChannelCount(int iMode, int &iCount);

    //////////////////////////////////////////////////////////////////////////
    // ����
    // ��ȡ������Ϣ
    long GetNetworkInfo(struNetworkInfo* pNI);
    // ����������Ϣ
    long SetNetworkInfo(const struNetworkInfo* pNI);
    
    // SIP������
    // ��ȡ������SIP��������Ϣ
    long GetSipServer(struSipServer* pSS);
    long SetSipServer(const char* szBuf);

    long GetDecOsdShow(struDecOsdInfo* posd);
    long SetDecOsdShow(struDecOsdInfo* posd);

    //////////////////////////////////////////////////////////////////////////
    // ϵͳ��Ϣ 
    // ��ȡMAC
    // szMAC: �����߷���64�ֽڿռ��ڴ�
    long GetDeviceMAC(char* szMAC);

    // ����MAC
    long SetDeviceMAC(const char* szMAC);
    
    // ��ȡ�豸�ͺ�
    long GetDeviceModel(int& iModel);
	long SetDeviceModel(int iModel);
    
    // ��ȡ�豸���к�
    // szSN�������߷���64�ֽ��ڴ�
    long GetDeviceSN(char* szSN);
    // �����豸���к�
    long SetDeviceSN(const char* szSN);
    
    // ��ȡ�豸��������汾��
    // szVer�������߷���64�ֽ��ڴ�
    long GetDeviceVer(char* szVer);

    // ��ȡϵͳ��󴴽�ʱ��
    // szTime�������߷���64�ֽ��ڴ�
    long GetDevBuildtime(char* szTime);

    //////////////////////////////////////////////////////////////////////////
    // ʱ��
    // ��ȡ��ǰʱ�䣬ʱ���ʽ��2013-10-10 10:10:10
    // szTime: �����߷���64�ֽ��ڴ�
    long GetTime(char* szTime);
    
    // ����ʱ�䣬ʱ���ʽ��2013-10-10 10:10:10
    long SetTime(const char* szTime);
    // ��ȡ������NTp
    long GetNtp(char* szBuf);
    long SetNtp(const char* szBuf);

    // �豸ά��
    // ��ȡ�豸����ʱ��
    // szUptime������������64�ֽ��ڴ�
    long GetDeviceUptime(char* szUptime);
    
    // ��ȡ������������, szHostname-64�ֽ��ַ���
    long GetHostname(char* szHostname);
    long SetHostname(const char* szHostname);

    // �����豸������1-ȫ�����裬2-�ֲ�����
    long ResetParam(int iType=1);
    
    // �����豸
    long RebootDevice();
    
    // �����豸
    long UpgradeDevice(const char* szData, unsigned long ulLen);

	// ��ȡ�����ý���ͨ����Ϣ
    long GetDecChannelInfo(struDecChannelInfo* pDCI);
    long SetDecChannelInfo(const struDecChannelInfo* pDCI);
    // ��ȡ�����÷ֱ���
    long GetResolution(struDisplayResolution* pDR);
    long SetResolution(const struDisplayResolution* pDR);
    // ��ȡ�����ö�̬����URL
    long GetDynamicDecUrl(struDynamicDecUrl* pDDU);
    long SetDynamicDecUrl(const struDynamicDecUrl* pDDU);

	// ��ȡ�������Զ�������Ϣ
    long GetAR(char* szBuf);
    long SetAR(const char* szBuf);

    //////////////////////////////////////////////////////////////////////////
    // �û���¼����֤
    void SetCB_UserLogin(UserLoginCB_T cbFun, void* pCBobj=NULL);
    //��ȡ�û���Ϣ���������
    void SetCB_GetUserInfo(GetUserInfoCB_T cbFun, void* pCBobj=NULL);
    // �޸��û���Ϣ
    void SetCB_EditUserInfo(EditUserInfoCB_T cbFun, void* pCBobj=NULL);
    // ���ûص�����
    // ��ȡ�������������
    void SetCB_GetNetworkInfo(GetNetworkInfoCB_T cbGetNI, void* pCBobj=NULL);
    void SetCB_SetNetworkInfo(SetNetworkInfoCB_T cbSetNI, void* pCBobj=NULL);
    void SetCB_GetSipServer(GetSipServerCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetSipServer(SetSipServerCB_T cbFun, void* pCBobj=NULL);
    void SetCB_UpgradeDev(UpgradeDevCB_T cbUD, void* pCBobj=NULL);
    void SetCB_GetDeviceMac(GetDeviceMacCB_T cbGetDM, void* pCBobj=NULL);
    void SetCB_SetDeviceMac(SetDeviceMacCB_T cbSetDM, void* pCBobj=NULL);
	// ��ȡ�����ý���ͨ����Ϣ
    void SetCB_GetDecChannelInfo(GetDecChannelInfoCB_T cbGetDCI, void* pCBobj=NULL);
    void SetCB_SetDecChannelInfo(SetDecChannelInfoCB_T cbSetDCI, void* pCBobj=NULL);
    // ���û�ȡ�����÷ֱ��ʻص�
    void SetCB_GetResolution(GetResolutionCB_T cbGetRes, void* pCBobj=NULL);
    void SetCB_SetResolution(SetResolutionCB_T cbSetRes, void* pCBobj=NULL);
    // ��ȡ�����ö�̬����URL�ص�
    void SetCB_GetDynamicDecUrl(GetDynamicDecUrlCB_T cbGetDDU, void* pCBobj=NULL);
    void SetCB_SetDynamicDecUrl(SetDynamicDecUrlCB_T cbSetDDU, void* pCBobj=NULL);
    // ������������ص�
    void SetCB_ResetParam(SetResetParamCB_T cbResetParam, void* pCBobj=NULL);
    // ��ȡ�������������ص�
    void SetCB_GetHostname(GetHostnameCB_T cbGetHostname, void* pCBobj=NULL);
    void SetCB_SetHostname(SetHostnameCB_T cbSetHostname, void* pCBobj=NULL);
    // ��ȡ�豸�ͺŻص�
    void SetCB_GetDeviceModel(GetDeviceModelCB_T cbFun, void* pCBobj=NULL);
	void SetCB_SetDeviceModel(SetDeviceModelCB_T cbFun, void* pCBobj=NULL);
    // ����/��ȡ�豸���кŻص�
    void SetCB_GetDeviceSN(GetDeviceSNCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetDeviceSN(SetDeviceSNCB_T cbFun, void* pCBobj=NULL);
    // ��ȡ�豸��������汾�Żص�
    void SetCB_GetDeviceVer(GetDeviceVerCB_T cbFun, void* pCBobj=NULL);
    void SetCB_GetDevBuildtime(GetDevBuildtimeCB_T cbFun, void* pCBobj=NULL);
    // ����ϵͳʱ��ص�
    void SetCB_SetSysTime(SetSysTimeCB_T cbFun, void* pCBobj=NULL);
    void SetCB_GetSysTime(GetSysTimeCB_T cbFun, void* pCBobj=NULL);    
    // ����NTP������IP��ַ�ص�
    void SetCB_GetNtp(GetNtpCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetNtp(SetNtpCB_T cbFun, void* pCBobj=NULL);
    // ��ȡ������OSD�ص�
    void SetCB_GetDecOsdShow(DecOsdShowCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetDecOsdShow(DecOsdShowCB_T cbFun, void* pCBobj=NULL);
    // ��ȡͨ������
    void SetCB_GetChannelCount(GetChannelCountCB_T cbFun, void* pCBobj=NULL);
	// �����Զ������ص�
    void SetCB_GetAR(GetARCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetAR(SetARCB_T cbFun, void* pCBobj=NULL);
private:
    // ת���ַ����еĿո�Ϊhtml�ո�&nbsp;
    // szValue��ת������ַ������ռ��ɵ����ߴ���
    long conv_space_html(const char* szStr, char* szValue);
    // ת���ַ����е�html�ո�&nbspΪ�ո�" ";
    // szValue��ת������ַ������ռ��ɵ����ߴ���
    long conv_html_space(const char* szStr, char* szValue);

private:
    CUser *m_pUser;
    CNetwork *m_pNetwork;
    CSysInfo *m_pSysInfo;
    CTimeCfg *m_pTimeCfg;
    CDevice  *m_pDevice;
    CWebDecoder * m_pWebDecoder;
private:
    // �ص���Ա   
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


