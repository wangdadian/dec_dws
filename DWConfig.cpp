#include "DWConfig.h"

UserLoginCB_T CDWConfig::m_cbUserLogin = NULL;
void* CDWConfig::m_pobjUserLogin = NULL;
GetUserInfoCB_T CDWConfig::m_cbGetUI = NULL;
void* CDWConfig::m_pobjGetUI = NULL;
EditUserInfoCB_T CDWConfig::m_cbEditUI = NULL;
void* CDWConfig::m_pobjEditUI = NULL;

GetSipServerCB_T CDWConfig::m_cbGetSipSvr = NULL;
void* CDWConfig::m_pobjGetSipSvr = NULL;
SetSipServerCB_T CDWConfig::m_cbSetSipSvr = NULL;
void* CDWConfig::m_pobjSetSipSvr = NULL;

GetNetworkInfoCB_T CDWConfig::m_cbGetNI = NULL;
void* CDWConfig::m_pobjGetNI = NULL;
SetNetworkInfoCB_T CDWConfig::m_cbSetNI = NULL;
void* CDWConfig::m_pobjSetNI = NULL;

UpgradeDevCB_T CDWConfig::m_cbUpgradeDev = NULL;
void* CDWConfig::m_pobjUD = NULL;

SetResetParamCB_T CDWConfig::m_cbResetParam = NULL;
void* CDWConfig::m_pobjResetParam = NULL;

GetHostnameCB_T CDWConfig::m_cbGetHostname = NULL;
void* CDWConfig::m_pobjGetHostname = NULL;
SetHostnameCB_T CDWConfig::m_cbSetHostname = NULL;
void* CDWConfig::m_pobjSetHostname = NULL;

GetDeviceMacCB_T CDWConfig::m_cbGetDM = NULL;
void* CDWConfig::m_pobjGetDM = NULL;
SetDeviceMacCB_T CDWConfig::m_cbSetDM = NULL;
void* CDWConfig::m_pobjSetDM = NULL;

GetDecChannelInfoCB_T CDWConfig::m_cbGetDCI = NULL;
void* CDWConfig::m_pobjGetDCI = NULL;    
SetDecChannelInfoCB_T CDWConfig::m_cbSetDCI = NULL;
void* CDWConfig::m_pobjSetDCI = NULL;

GetResolutionCB_T CDWConfig::m_cbGetRes = NULL;
void* CDWConfig::m_pobjGetRes = NULL;
SetResolutionCB_T CDWConfig::m_cbSetRes = NULL;
void* CDWConfig::m_pobjSetRes = NULL;

GetDynamicDecUrlCB_T CDWConfig::m_cbGetDDU = NULL;
void* CDWConfig::m_pobjGetDDU = NULL;
SetDynamicDecUrlCB_T CDWConfig::m_cbSetDDU = NULL;
void* CDWConfig::m_pobjSetDDU = NULL;

GetDeviceModelCB_T CDWConfig::m_cbGetModel = NULL;
void* CDWConfig::m_pobjGetModel = NULL;
SetDeviceModelCB_T CDWConfig::m_cbSetModel = NULL;
void* CDWConfig::m_pobjSetModel = NULL;
GetDeviceSNCB_T CDWConfig::m_cbGetSN = NULL;
void* CDWConfig::m_pobjGetSN = NULL;
SetDeviceSNCB_T CDWConfig::m_cbSetSN = NULL;
void* CDWConfig::m_pobjSetSN = NULL;    
GetDeviceVerCB_T CDWConfig::m_cbGetVer = NULL;
void* CDWConfig::m_pobjGetVer = NULL;
GetDevBuildtimeCB_T CDWConfig::m_cbGetBT = NULL;
void* CDWConfig::m_pobjGetBT = NULL;

SetSysTimeCB_T CDWConfig::m_cbSetSysTime = NULL;
void* CDWConfig::m_pobjSetSysTime = NULL;
GetSysTimeCB_T CDWConfig::m_cbGetSysTime = NULL;
void* CDWConfig::m_pobjGetSysTime = NULL;

GetNtpCB_T CDWConfig::m_cbGetNtp = NULL;
void* CDWConfig::m_pobjGetNtp = NULL;
SetNtpCB_T CDWConfig::m_cbSetNtp = NULL;
void* CDWConfig::m_pobjSetNtp = NULL;

DecOsdShowCB_T CDWConfig::m_cbGetDecOsdShow = NULL;
void* CDWConfig::m_pobjGetDecOsdShow = NULL;
DecOsdShowCB_T CDWConfig::m_cbSetDecOsdShow = NULL;
void* CDWConfig::m_pobjSetDecOsdShow = NULL;

GetChannelCountCB_T CDWConfig::m_cbGetChnCnt = NULL;
void* CDWConfig::m_pobjGetChnCnt = NULL;

GetARCB_T  CDWConfig::m_cbGetAR = NULL;
void*  CDWConfig::m_pobjGetAR = NULL;
SetARCB_T  CDWConfig::m_cbSetAR = NULL;
void*  CDWConfig::m_pobjSetAR = NULL;


CDWConfig::CDWConfig()
{
    m_pUser = new CUser;
    m_pNetwork = new CNetwork;
    m_pSysInfo = new CSysInfo;
    m_pTimeCfg = new CTimeCfg;
    m_pWebDecoder = new CWebDecoder;
}

CDWConfig::~CDWConfig()
{
    PTR_DELETE(m_pUser);
    PTR_DELETE(m_pNetwork);
    PTR_DELETE(m_pSysInfo);
    PTR_DELETE(m_pTimeCfg);
    PTR_DELETE(m_pWebDecoder);
}

// 获取通道个数
long CDWConfig::GetChannelCount(int iMode, int &iCount)
{
    if ( m_cbGetChnCnt != NULL ) {
        long lRet =  m_cbGetChnCnt(iMode, iCount, m_pobjGetChnCnt);
        return lRet;
    }
    
    return RET_FAILED;
}

long CDWConfig::UserLogin(char* szUserName, char* szPassword)
{
    //long lRet = m_pUser->UserLogin(szUserName, szPassword);
    //return lRet;
    if ( m_cbUserLogin != NULL ) {
        long lRet =  m_cbUserLogin(szUserName, szPassword, m_pobjUserLogin);
        return lRet;
    }
    
    return RET_FAILED;
}
long CDWConfig::GetUserInfo(struUserInfo* &pUserInfo, int &iUserCount)
{
    //long lRet = m_pUser->GetUserInfo(pUserInfo, iUserCount);
    //return lRet;
    if ( m_cbGetUI != NULL ) {
        long lRet =  m_cbGetUI(pUserInfo, iUserCount, m_pobjGetUI);
        return lRet;
    }
    
    return RET_FAILED;
}
// 修改用户信息
long CDWConfig::EditUserInfo(const struUserInfo* pUserInfo)
{
    //long lRet = m_pUser->EditUserInfo(pUserInfo);
    //return lRet;
    if ( m_cbEditUI != NULL ) {
        long lRet =  m_cbEditUI(pUserInfo, m_pobjEditUI);
        return lRet;
    }
    
    return RET_FAILED;
}
// 获取网络信息
long CDWConfig::GetNetworkInfo(struNetworkInfo* pNI)
{
    if ( m_cbGetNI != NULL ) {
        long lRet =  m_cbGetNI(pNI, m_pobjGetNI);
        return lRet;
    }
    
    return RET_FAILED;
}

// 设置网络信息
long CDWConfig::SetNetworkInfo(const struNetworkInfo* pNI)
{
    if ( m_cbSetNI != NULL ) {
        long lRet =  m_cbSetNI(pNI, m_pobjSetNI);
        return lRet;
    }

    return RET_FAILED;
}
// SIP服务器
// 获取、设置SIP服务器信息
long CDWConfig::GetSipServer(struSipServer* pSS)
{
    if ( m_cbGetSipSvr != NULL ) {
        long lRet =  m_cbGetSipSvr(pSS, m_pobjGetSipSvr);
        return lRet;
    }
    
    return RET_FAILED;
}
long CDWConfig::SetSipServer(const char* szBuf)
{
    if ( m_cbSetSipSvr != NULL ) {
        long lRet =  m_cbSetSipSvr(szBuf, m_pobjSetSipSvr);
        return lRet;
    }
    
    return RET_FAILED;
}
long CDWConfig::GetDecOsdShow(struDecOsdInfo* posd)
{
    if ( m_cbGetDecOsdShow != NULL ) {
        long lRet =  m_cbGetDecOsdShow(posd, m_pobjGetDecOsdShow);
        return lRet;
    }
    
    return RET_FAILED;
}
long CDWConfig::SetDecOsdShow(struDecOsdInfo* posd)
{
    if ( m_cbSetDecOsdShow != NULL ) {
        long lRet =  m_cbSetDecOsdShow(posd, m_pobjSetDecOsdShow);
        return lRet;
    }
    
    return RET_FAILED;
}
// 获取MAC
// szMAC: 调用者分配64字节空间内存
long CDWConfig::GetDeviceMAC(char* szMAC)
{
    if ( m_cbGetDM != NULL ) {
        long lRet =  m_cbGetDM(szMAC, m_pobjGetDM);
        return lRet;
    }
    
    return RET_FAILED;
}

// 获取MAC
long CDWConfig::SetDeviceMAC(const char* szMAC)
{
    if ( m_cbSetDM != NULL ) {
        long lRet =  m_cbSetDM(szMAC, m_pobjSetDM);
        return lRet;
    }
    
    return RET_FAILED;
}

// 获取设备型号
// szModel: 调用者分配64字节内存
long CDWConfig::GetDeviceModel(int& iModel)
{
    if ( m_cbGetModel != NULL ) {
        long lRet =  m_cbGetModel(iModel, m_pobjGetModel);
        return lRet;
    }
    
    return RET_FAILED;
}
long CDWConfig::SetDeviceModel(int iModel)
{
	if ( m_cbSetModel != NULL ) {
		long lRet =  m_cbSetModel(iModel, m_pobjSetModel);
		return lRet;
	}

	return RET_FAILED;
}
// 获取设备序列号
// szModel：调用者分配64字节内存
long CDWConfig::GetDeviceSN(char* szSN)
{
    if ( m_cbGetSN != NULL ) {
        long lRet =  m_cbGetSN(szSN, m_pobjGetSN);
        return lRet;
    }
    
    return RET_FAILED;
}
// 设置设备序列号
// szModel：调用者分配64字节内存
long CDWConfig::SetDeviceSN(const char* szSN)
{
    if ( m_cbSetSN != NULL ) {
        long lRet =  m_cbSetSN(szSN, m_pobjSetSN);
        return lRet;
    }
    
    return RET_FAILED;
}
// 获取设备主控软件版本号
// szVer：调用者分配64字节内存
long CDWConfig::GetDeviceVer(char* szVer)
{
    if ( m_cbGetVer != NULL ) {
        long lRet =  m_cbGetVer(szVer, m_pobjGetVer);
        return lRet;
    }
    
    return RET_FAILED;
}
// 获取系统最后更新时间
// szTime：调用者分配64字节内存
long CDWConfig::GetDevBuildtime(char* szTime)
{
    if ( m_cbGetBT != NULL ) {
        long lRet =  m_cbGetBT(szTime, m_pobjGetBT);
        return lRet;
    }
    
    return RET_FAILED;
}

// 获取当前时间，时间格式：2013-10-10 10:10:10
// szTime: 调用者分配64字节内存
long CDWConfig::GetTime(char* szTime)
{
/*
    long lRet = m_pTimeCfg->GetTime(szTime);
    char szValue[200] = {0};
    conv_space_html(szTime, szValue);
    sprintf(szTime, szValue);
    return lRet;
    */    
    if ( m_cbGetSysTime != NULL ) {
        long lRet = m_cbGetSysTime(szTime, m_pobjGetSysTime);
        char szValue[200] = {0};
        conv_space_html(szTime, szValue);
        sprintf(szTime, szValue);
        return lRet;
    }
    return RET_FAILED;
}

// 设置时间，时间格式：2013-10-10 10:10:10
long CDWConfig::SetTime(const char* szTime)
{
    if ( m_cbSetSysTime != NULL ) {
        char szValue[200] = {0};
        conv_html_space(szTime, szValue);
        long lRet = m_cbSetSysTime(szValue, m_pobjSetSysTime);
        return lRet;
    }
    return RET_FAILED;
}
// 获取、设置NTP服务器IP地址
long CDWConfig::GetNtp(char* szBuf)
{
    if ( m_cbGetNtp != NULL ) {
        long lRet = m_cbGetNtp(szBuf, m_pobjGetNtp);
        return lRet;
    }
    return RET_FAILED;
}
long CDWConfig::SetNtp(const char* szBuf)
{
    if ( m_cbSetNtp != NULL ) {
        long lRet = m_cbSetNtp(szBuf, m_pobjSetNtp);
        return lRet;
    }
    return RET_FAILED;
}
// 获取设备运行时间
// szUptime：调用者申请64字节内存
long CDWConfig::GetDeviceUptime(char* szUptime)
{
    long lRet = m_pDevice->GetDeviceUptime(szUptime);
    char szValue[200] = {0};
    conv_space_html(szUptime, szValue);
    sprintf(szUptime, szValue);
    return lRet;
}

// 重设设备参数
long CDWConfig::ResetParam(int iType)
{
    if ( m_cbResetParam != NULL ) {
        long lRet = m_cbResetParam(iType, m_pobjResetParam);
        return lRet;
    }
    return RET_FAILED;
}

// 获取设置主机名称, szHostname-64字节字符串
long CDWConfig::GetHostname(char* szHostname)
{
    if ( m_cbGetHostname != NULL ) {
        long lRet =  m_cbGetHostname(szHostname, m_pobjGetHostname);
        return lRet;
    }
    return RET_FAILED;
}
long CDWConfig::SetHostname(const char* szHostname)
{
    if ( m_cbSetHostname != NULL ) {
        long lRet = m_cbSetHostname(szHostname, m_pobjSetHostname);
        return lRet;
    }
    return RET_FAILED;
}

// 重启设备
long CDWConfig::RebootDevice()
{
    long lRet =  m_pDevice->RebootDevice();
    return lRet;
}

// 升级设备
long CDWConfig::UpgradeDevice(const char* szData, unsigned long ulLen)
{
    if ( m_cbUpgradeDev != NULL ) {
        long lRet =  m_cbUpgradeDev(szData, ulLen, m_pobjUD);
        return lRet;
    }
    return RET_FAILED;
}

// 获取、设置分辨率
long CDWConfig::GetResolution(struDisplayResolution* pDR)
{
    if ( m_cbGetRes != NULL ) {
        long lRet = m_cbGetRes(pDR, m_pobjGetRes);
        return lRet;
    }
    return RET_FAILED;
}

long CDWConfig::SetResolution(const struDisplayResolution* pDR)
{
    if ( m_cbGetRes != NULL ) {
        long lRet = m_cbSetRes(pDR, m_pobjSetRes);
        return lRet;
    }
    return RET_FAILED;
}

// 获取、设置动态解码URL
long CDWConfig::GetDynamicDecUrl(struDynamicDecUrl* pDDU)
{
    if ( m_cbGetDDU != NULL ) {
        long lRet = m_cbGetDDU(pDDU, m_pobjGetDDU);
        return lRet;
    }
    return RET_FAILED;
}
long CDWConfig::SetDynamicDecUrl(const struDynamicDecUrl* pDDU)
{
    if ( m_cbSetDDU != NULL ) {
        long lRet = m_cbSetDDU(pDDU, m_pobjSetDDU);
        return lRet;
    }
    return RET_FAILED;
}
// 获取、设置解码通道信息
long CDWConfig::GetDecChannelInfo(struDecChannelInfo* pDCI)
{
    if ( m_cbGetDCI != NULL ) {
        long lRet = m_cbGetDCI(pDCI, m_pobjGetDCI);
        return lRet;
    }
    return RET_FAILED;
}
long CDWConfig::SetDecChannelInfo(const struDecChannelInfo* pDCI)
{
    if ( m_cbSetDCI != NULL ) {
        long lRet = m_cbSetDCI(pDCI, m_pobjSetDCI);
        return lRet;
    }
    return RET_FAILED;
}

// 获取、设置自动重启信息
long CDWConfig::GetAR(char* szBuf)
{
    if ( m_cbGetAR != NULL ) {
        long lRet = m_cbGetAR(szBuf, m_pobjGetAR);
        return lRet;
    }
    return RET_FAILED;
}
long CDWConfig::SetAR(const char* szBuf)
{
    if ( m_cbSetAR != NULL ) {
        long lRet = m_cbSetAR(szBuf, m_pobjSetAR);
        return lRet;
    }
    return RET_FAILED;
}
//////////////////////////////////////////////////////////////////////////


void CDWConfig::SetCB_GetNetworkInfo(GetNetworkInfoCB_T cbGetNI, void* pCBobj)
{
    if (cbGetNI == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetNI = cbGetNI;
    m_pobjGetNI = pCBobj;
}

void CDWConfig::SetCB_SetNetworkInfo(SetNetworkInfoCB_T cbSetNI, void* pCBobj)
{
    if (cbSetNI == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetNI = cbSetNI;
    m_pobjSetNI = pCBobj;
}
void CDWConfig::SetCB_GetSipServer(GetSipServerCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetSipSvr = cbFun;
    m_pobjGetSipSvr = pCBobj;
}
void CDWConfig::SetCB_SetSipServer(SetSipServerCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetSipSvr = cbFun;
    m_pobjSetSipSvr = pCBobj;
}
void CDWConfig::SetCB_UpgradeDev(UpgradeDevCB_T cbUD, void* pCBobj)
{
    if (cbUD == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbUpgradeDev = cbUD;
    m_pobjUD = pCBobj;
}

void CDWConfig::SetCB_GetDeviceMac(GetDeviceMacCB_T cbGetDM, void* pCBobj)
{
    if (cbGetDM == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetDM = cbGetDM;
    m_pobjGetDM = pCBobj;
}

void CDWConfig::SetCB_SetDeviceMac(SetDeviceMacCB_T cbSetDM, void* pCBobj)
{
    if (cbSetDM == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetDM = cbSetDM;
    m_pobjSetDM = pCBobj;
}

long CDWConfig::conv_space_html(const char* szStr, char* szValue)
{
    // &nbsp;
    if (szStr==NULL || szValue==NULL) {
        return RET_FAILED;
    }
    int iLen = strlen(szStr);
    if (iLen<=0) {
        return RET_FAILED;
    }
    char* szTmpStr = new char[iLen];
    memcpy(szTmpStr, szStr, sizeof(char)*iLen);
    int index = 0;
    for(int i=0; i<iLen; i++)
    {
        if ( szTmpStr[i] != ' ' )
        {
            szValue[index] = szTmpStr[i];
            index+=1;
        }
        else
        {
            sprintf(&szValue[index], "%s", "&nbsp;");
            index+=6;
        }
    }
    szValue[index] = '\0';
    delete [] szTmpStr;
    szTmpStr = NULL;
    return RET_SUCCESS;
}

long CDWConfig::conv_html_space(const char* szStr, char* szValue)
{
    // &nbsp;
    if (szStr==NULL || szValue==NULL) {
        return RET_FAILED;
    }
    int iLen = strlen(szStr);
    if (iLen<=0) {
        return RET_FAILED;
    }
    char* szTmpStr = new char[iLen];
    memcpy(szTmpStr, szStr, sizeof(char)*iLen);
    int index_s = 0;
    int index_v = 0;
    int iToCopy = 0;
    char *ptr = NULL;
    while( true ){
        ptr = NULL;
        ptr = strstr(&szTmpStr[index_s], "&nbsp;");
        if (ptr == NULL) {
            sprintf(&szValue[index_v], "%s", &szTmpStr[index_s]);
            break;
        }
        iToCopy = abs(szTmpStr - ptr) - index_s;
        if ( iToCopy > 0 ) {
            strncpy(&szValue[index_v], &szTmpStr[index_s], iToCopy);
        }
        index_v += iToCopy;
        index_s += (iToCopy + 6);
        szValue[index_v] = ' ';
        index_v += 1;
        if (index_s >= iLen) {
            break;
        }
    }
    delete [] szTmpStr;
    szTmpStr = NULL;
    return RET_SUCCESS;
}
// 获取、设置解码通道信息
void CDWConfig::SetCB_GetDecChannelInfo(GetDecChannelInfoCB_T cbGetDCI, void* pCBobj)
{
    if (cbGetDCI == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetDCI   = cbGetDCI;
    m_pobjGetDCI = pCBobj;
}
void CDWConfig::SetCB_SetDecChannelInfo(SetDecChannelInfoCB_T cbSetDCI, void* pCBobj)
{
    if (cbSetDCI == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetDCI   = cbSetDCI;
    m_pobjSetDCI = pCBobj;
}
// 设置获取、设置分辨率回调
void CDWConfig::SetCB_GetResolution(GetResolutionCB_T cbGetRes, void* pCBobj)
{
    if (cbGetRes == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetRes   = cbGetRes;
    m_pobjGetRes = pCBobj;
}

void CDWConfig::SetCB_SetResolution(SetResolutionCB_T cbSetRes, void* pCBobj)
{
    if (cbSetRes == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetRes   = cbSetRes;
    m_pobjSetRes = pCBobj;
}

// 获取、设置动态解码URL回调
void CDWConfig::SetCB_GetDynamicDecUrl(GetDynamicDecUrlCB_T cbGetDDU, void* pCBobj)
{
    if (cbGetDDU == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetDDU   = cbGetDDU;
    m_pobjGetDDU = pCBobj;
}
void CDWConfig::SetCB_SetDynamicDecUrl(SetDynamicDecUrlCB_T cbSetDDU, void* pCBobj)
{
    if (cbSetDDU == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetDDU   = cbSetDDU;
    m_pobjSetDDU = pCBobj;
}

// 设置重设参数回调
void CDWConfig::SetCB_ResetParam(SetResetParamCB_T cbResetParam, void* pCBobj)
{
    if (cbResetParam == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbResetParam   = cbResetParam;
    m_pobjResetParam = pCBobj;
}

// 获取、设置主机名回调
void CDWConfig::SetCB_GetHostname(GetHostnameCB_T cbGetHostname, void* pCBobj)
{
    if (cbGetHostname == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetHostname   = cbGetHostname;
    m_pobjGetHostname = pCBobj;
}

void CDWConfig::SetCB_SetHostname(SetHostnameCB_T cbSetHostname, void* pCBobj)
{
    if (cbSetHostname == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetHostname   = cbSetHostname;
    m_pobjSetHostname = pCBobj;
}
// 用户登录及验证
void CDWConfig::SetCB_UserLogin(UserLoginCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbUserLogin   = cbFun;
    m_pobjUserLogin = pCBobj;
}
//获取用户信息，密码填空
void CDWConfig::SetCB_GetUserInfo(GetUserInfoCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetUI   = cbFun;
    m_pobjGetUI = pCBobj;
}
void CDWConfig::SetCB_EditUserInfo(EditUserInfoCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbEditUI   = cbFun;
    m_pobjEditUI = pCBobj;
}
void CDWConfig::SetCB_SetSysTime(SetSysTimeCB_T cbFun, void* pCBobj/* =NULL */)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetSysTime   = cbFun;
    m_pobjSetSysTime = pCBobj;
}
void CDWConfig::SetCB_GetSysTime(GetSysTimeCB_T cbFun, void* pCBobj/* =NULL */)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetSysTime   = cbFun;
    m_pobjGetSysTime = pCBobj;
}
void CDWConfig::SetCB_GetDeviceModel(GetDeviceModelCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetModel   = cbFun;
    m_pobjGetModel = pCBobj;
}
void CDWConfig::SetCB_SetDeviceModel(SetDeviceModelCB_T cbFun, void* pCBobj)
{
	if (cbFun == NULL) {
		//printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
		return;
	}
	m_cbSetModel   = cbFun;
	m_pobjSetModel = pCBobj;
}
void CDWConfig::SetCB_GetDeviceSN(GetDeviceSNCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetSN   = cbFun;
    m_pobjGetSN = pCBobj;
}
void CDWConfig::SetCB_SetDeviceSN(SetDeviceSNCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetSN   = cbFun;
    m_pobjSetSN = pCBobj;
}
void CDWConfig::SetCB_GetDeviceVer(GetDeviceVerCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetVer   = cbFun;
    m_pobjGetVer = pCBobj;
}
void CDWConfig::SetCB_GetDevBuildtime(GetDevBuildtimeCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetBT   = cbFun;
    m_pobjGetBT = pCBobj;
}
// 设置NTP服务器IP地址回调
void CDWConfig::SetCB_GetNtp(GetNtpCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetNtp   = cbFun;
    m_pobjGetNtp = pCBobj;
}
void CDWConfig::SetCB_SetNtp(SetNtpCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetNtp   = cbFun;
    m_pobjSetNtp = pCBobj;
}

// 获取通道个数
void CDWConfig::SetCB_GetChannelCount(GetChannelCountCB_T cbFun, void* pCBobj)
{    
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetChnCnt   = cbFun;
    m_pobjGetChnCnt = pCBobj;
}
// 获取、设置OSD回调
void CDWConfig::SetCB_GetDecOsdShow(DecOsdShowCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetDecOsdShow   = cbFun;
    m_pobjGetDecOsdShow = pCBobj;
}
void CDWConfig::SetCB_SetDecOsdShow(DecOsdShowCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetDecOsdShow   = cbFun;
    m_pobjSetDecOsdShow = pCBobj;
}

// 设置自动重启回调
void CDWConfig::SetCB_GetAR(GetARCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetAR   = cbFun;
    m_pobjGetAR = pCBobj;
}
void CDWConfig::SetCB_SetAR(SetARCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetAR   = cbFun;
    m_pobjSetAR = pCBobj;
}

