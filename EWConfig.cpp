// EWConfig.cpp: implementation of the CEWConfig class.
//
//////////////////////////////////////////////////////////////////////

#include "EWConfig.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
GetEncAlarminCB_T CEWConfig::m_cbGetEncAlarmin = NULL;
void* CEWConfig::m_pobjGetEncAlarmin = NULL; 
GetEncAlarmoutCB_T CEWConfig::m_cbGetEncAlarmout = NULL;
void* CEWConfig::m_pobjGetEncAlarmout = NULL;
SetEncAlarmCB_T CEWConfig::m_cbSetEncAlarm = NULL;
void* CEWConfig::m_pobjSetEncAlarm = NULL;

GetEncChannelCB_T CEWConfig::m_cbGetEncChn = NULL;
void* CEWConfig::m_pobjGetEncChn = NULL;
SetEncChannelCB_T CEWConfig::m_cbSetEncChn = NULL;
void* CEWConfig::m_pobjSetEncChn = NULL;

GetEncDisplayCB_T CEWConfig::m_cbGetEncDsp = NULL;
void* CEWConfig::m_pobjGetEncDsp = NULL;
SetEncDisplayCB_T CEWConfig::m_cbSetEncDsp = NULL;
void* CEWConfig::m_pobjSetEncDsp = NULL;

GetEncTransferCB_T CEWConfig::m_cbGetEncTrans = NULL;
void* CEWConfig::m_pobjGetEncTrans = NULL;
SetEncTransferCB_T CEWConfig::m_cbSetEncTrans = NULL;
void* CEWConfig::m_pobjSetEncTrans = NULL;

GetEncVideoCB_T CEWConfig::m_cbGetEncVideo = NULL;
void* CEWConfig::m_pobjGetEncVideo = NULL;
SetEncVideoCB_T CEWConfig::m_cbSetEncVideo = NULL;
void* CEWConfig::m_pobjSetEncVideo = NULL;

GetEncPtzPortCB_T CEWConfig::m_cbGetEncPtzPort = NULL;
void* CEWConfig::m_pobjGetEncPtzPort = NULL;
SetEncPtzPortCB_T CEWConfig::m_cbSetEncPtzPort = NULL;
void* CEWConfig::m_pobjSetEncPtzPort = NULL;

GetEncForwardportCB_T CEWConfig::m_cbGetEncForwardport = NULL;
void* CEWConfig::m_pobjGetEncForwardport = NULL;
SetEncForwardportCB_T CEWConfig::m_cbSetEncForwardport = NULL;
void* CEWConfig::m_pobjSetEncForwardport = NULL;

CEWConfig::CEWConfig()
{

}

CEWConfig::~CEWConfig()
{

}

//////////////////////////////////////////////////////////////////////////
// 获取、设置编码器透明端口信息
long CEWConfig::GetEncForwardport(char* szBuf)
{
    if ( m_cbGetEncForwardport != NULL ) {
        long lRet =  m_cbGetEncForwardport(szBuf, m_pobjGetEncForwardport);
        return lRet;
    }
    return RET_FAILED; 
}
long CEWConfig::SetEncForwardport(const char* szBuf)
{
    if ( m_cbSetEncForwardport != NULL ) {
        long lRet =  m_cbSetEncForwardport(szBuf, m_pobjSetEncForwardport);
        return lRet;
    }
    return RET_FAILED; 
}
// 获取、设置编码器PTZ通道信息
long CEWConfig::GetEncPtzPort(char* szBuf)
{
    if ( m_cbGetEncPtzPort != NULL ) {
        long lRet =  m_cbGetEncPtzPort(szBuf, m_pobjGetEncPtzPort);
        return lRet;
    }
    return RET_FAILED; 
}
long CEWConfig::SetEncPtzPort(const char* szBuf)
{
    if ( m_cbSetEncPtzPort != NULL ) {
        long lRet =  m_cbSetEncPtzPort(szBuf, m_pobjSetEncPtzPort);
        return lRet;
    }
    return RET_FAILED; 
}
// 获取、设置编码器通道信息
long CEWConfig::GetEncChannel(char* szBuf, int chnno)
{
    if ( m_cbGetEncChn != NULL ) {
        long lRet =  m_cbGetEncChn(szBuf, chnno, m_pobjGetEncChn);
        return lRet;
    }
    return RET_FAILED; 
}

long CEWConfig::SetEncChannel(const char* szBuf)
{
    if ( m_cbSetEncChn != NULL ) {
        long lRet =  m_cbSetEncChn(szBuf, m_pobjSetEncChn);
        return lRet;
    }
    return RET_FAILED; 
}

// 获取编码器通道显示信息
long CEWConfig::GetEncDisplay(char* szBuf, int chnno)
{
    if ( m_cbGetEncDsp != NULL ) {
        long lRet =  m_cbGetEncDsp(szBuf, chnno, m_pobjGetEncDsp);
        return lRet;
    }
    return RET_FAILED; 
}

// 设置编码器通道显示信息
long CEWConfig::SetEncDisplay(const char* szBuf)
{
    if ( m_cbSetEncDsp != NULL ) {
        long lRet =  m_cbSetEncDsp(szBuf,m_pobjSetEncDsp);
        return lRet;
    }
    return RET_FAILED;
}
// 获取、设置编码器通道码流传输信息
long CEWConfig::GetEncTransfer(char* szBuf, int chnno)
{   
    if ( m_cbGetEncTrans != NULL ) {
        long lRet =  m_cbGetEncTrans(szBuf, chnno, m_pobjGetEncTrans);
        return lRet;
    }
    return RET_FAILED;
}
long CEWConfig::SetEncTransfer(const char* szBuf)
{   
    if ( m_cbSetEncTrans != NULL ) {
        long lRet =  m_cbSetEncTrans(szBuf, m_pobjSetEncTrans);
        return lRet;
    }
    return RET_FAILED;
}
// 获取、设置编码器通道码流信息
long CEWConfig::GetEncVideo(char* szBuf, int chnno)
{   
    if ( m_cbGetEncVideo != NULL ) {
        long lRet =  m_cbGetEncVideo(szBuf, chnno, m_pobjGetEncVideo);
        return lRet;
    }
    return RET_FAILED;
}
long CEWConfig::SetEncVideo(const char* szBuf)
{   
    if ( m_cbSetEncVideo != NULL ) {
        long lRet =  m_cbSetEncVideo(szBuf, m_pobjSetEncVideo);
        return lRet;
    }
    return RET_FAILED;
}
// 获取、设置编码器报警信息
long CEWConfig::GetEncAlarmin(char* szBuf, int no)
{
    if ( m_cbGetEncAlarmin != NULL ) {
        long lRet =  m_cbGetEncAlarmin(szBuf, no, m_pobjGetEncAlarmin);
        return lRet;
    }
    return RET_FAILED;
}
long CEWConfig::GetEncAlarmout(char* szBuf, int no)
{
    if ( m_cbGetEncAlarmout != NULL ) {
        long lRet =  m_cbGetEncAlarmout(szBuf, no, m_pobjGetEncAlarmout);
        return lRet;
    }
    return RET_FAILED;
}
long CEWConfig::SetEncAlarm(const char* szBuf)
{
    if ( m_cbSetEncAlarm != NULL ) {
        long lRet =  m_cbSetEncAlarm(szBuf, m_pobjSetEncAlarm);
        return lRet;
    }
    return RET_FAILED;
}
//////////////////////////////////////////////////////////////////////////
// 设置回调函数
// 获取、设置透明端口的回调
void CEWConfig::SetCB_GetEncForwardport(GetEncForwardportCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetEncForwardport   = cbFun;
    m_pobjGetEncForwardport = pCBobj;
}
void CEWConfig::SetCB_SetEncForwardport(SetEncForwardportCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetEncForwardport   = cbFun;
    m_pobjSetEncForwardport = pCBobj;
}
// 获取、设置通PTZ端口的回调
void CEWConfig::SetCB_GetEncPtzPort(GetEncPtzPortCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetEncPtzPort   = cbFun;
    m_pobjGetEncPtzPort = pCBobj;
}
void CEWConfig::SetCB_SetEncPtzPort(SetEncPtzPortCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetEncPtzPort   = cbFun;
    m_pobjSetEncPtzPort = pCBobj;
}
// 获取、设置编码器报警信息的回调
void CEWConfig::SetCB_GetEncAlarmin(GetEncAlarminCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetEncAlarmin   = cbFun;
    m_pobjGetEncAlarmin = pCBobj;
}
void CEWConfig::SetCB_GetEncAlarmout(GetEncAlarmoutCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetEncAlarmout   = cbFun;
    m_pobjGetEncAlarmout = pCBobj;
}
void CEWConfig::SetCB_SetEncAlarm(SetEncAlarmCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetEncAlarm   = cbFun;
    m_pobjSetEncAlarm = pCBobj;
}
// 获取、设置通道信息的回调
void CEWConfig::SetCB_GetEncChannel(GetEncChannelCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetEncChn   = cbFun;
    m_pobjGetEncChn = pCBobj;
}

void CEWConfig::SetCB_SetEncChannel(SetEncChannelCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetEncChn   = cbFun;
    m_pobjSetEncChn = pCBobj;
}

// 获取OSD显示信息的回调
void CEWConfig::SetCB_GetEncDisplay(GetEncDisplayCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetEncDsp   = cbFun;
    m_pobjGetEncDsp = pCBobj;
}
// 设置OSD显示信息的回调
void CEWConfig::SetCB_SetEncDisplay(SetEncDisplayCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetEncDsp   = cbFun;
    m_pobjSetEncDsp = pCBobj;
}

// 获取、设置码流传输信息的回调
void CEWConfig::SetCB_GetEncTransfer(GetEncTransferCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetEncTrans   = cbFun;
    m_pobjGetEncTrans = pCBobj;
}
void CEWConfig::SetCB_SetEncTransfer(SetEncTransferCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetEncTrans   = cbFun;
    m_pobjSetEncTrans = pCBobj;
}
// 获取、设置码流信息的回调
void CEWConfig::SetCB_GetEncVideo(GetEncVideoCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbGetEncVideo   = cbFun;
    m_pobjGetEncVideo = pCBobj;
}
void CEWConfig::SetCB_SetEncVideo(SetEncVideoCB_T cbFun, void* pCBobj)
{
    if (cbFun == NULL) {
        //printf("%s:%s:%s: CALLBACK NULL!\n", __FILE__,__LINE__,__FUNCTION__);
        return;
    }
    m_cbSetEncVideo   = cbFun;
    m_pobjSetEncVideo = pCBobj;
}



