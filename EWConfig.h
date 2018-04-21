// EWConfig.h: interface for the CEWConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EWCONFIG_H__2D79C4D4_5C3B_4688_BB79_392D8BCA3245__INCLUDED_)
#define AFX_EWCONFIG_H__2D79C4D4_5C3B_4688_BB79_392D8BCA3245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "define.h"
#include "Facility.h"
#include "dwstype.h"

// 函数类型
// 设置、获取透明端口信息
typedef long (*GetEncForwardportCB_T)(char* szBuf, void* param);
typedef long (*SetEncForwardportCB_T)(const char* szBuf, void* param);
// 设置、获取Ptz端口信息
typedef long (*GetEncPtzPortCB_T)(char* szBuf, void* param);
typedef long (*SetEncPtzPortCB_T)(const char* szBuf, void* param);
// 设置、获取报警信息
typedef long (*GetEncAlarminCB_T)(char* szBuf, int no, void* param);
typedef long (*GetEncAlarmoutCB_T)(char* szBuf, int no, void* param);
typedef long (*SetEncAlarmCB_T)(const char* szBuf, void* param);
// 设置、获取通道信息
typedef long (*GetEncChannelCB_T)(char* szBuf, int chnno, void* param);
typedef long (*SetEncChannelCB_T)(const char* szBuf, void* param);
// 设置、获取OSD显示
typedef long (*GetEncDisplayCB_T)(char* szBuf, int chnno, void* param);
typedef long (*SetEncDisplayCB_T)(const char* szBuf, void* param);
// 获取、设置编码通道码流传输信息
typedef long (*GetEncTransferCB_T)(char* szBuf, int chnno, void* param);
typedef long (*SetEncTransferCB_T)(const char* szBuf, void* param);
// 获取、设置编码通道码流信息
typedef long (*GetEncVideoCB_T)(char* szBuf, int chnno, void* param);
typedef long (*SetEncVideoCB_T)(const char* szBuf, void* param);

class CEWConfig  
{
public:
	CEWConfig();
	virtual ~CEWConfig();

    //////////////////////////////////////////////////////////////////////////
    // 获取、设置编码器透明端口信息
    long GetEncForwardport(char* szBuf);
    long SetEncForwardport(const char* szBuf);
    // 获取、设置编码器PTZ控制端口信息
    long GetEncPtzPort(char* szBuf);
    long SetEncPtzPort(const char* szBuf);
    
    // 获取、设置编码器通道信息
    long GetEncChannel(char* szBuf, int chnno);
    long SetEncChannel(const char* szBuf);

    // 获取、设置编码器通道显示信息
    long GetEncDisplay(char* szBuf, int chnno);
    long SetEncDisplay(const char* szBuf);

    // 获取、设置编码器通道码流传输信息
    long GetEncTransfer(char* szBuf, int chnno);
    long SetEncTransfer(const char* szBuf);

    // 获取、设置编码器通道码流信息
    long GetEncVideo(char* szBuf, int chnno);
    long SetEncVideo(const char* szBuf);

    // 获取、设置编码器报警信息
    long GetEncAlarmin(char* szBuf, int no);
    long GetEncAlarmout(char* szBuf, int no);
    long SetEncAlarm(const char* szBuf);
    //////////////////////////////////////////////////////////////////////////
    // 设置回调函数
    // 获取、设置透明端口的回调
    void SetCB_GetEncForwardport(GetEncPtzPortCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncForwardport(SetEncPtzPortCB_T cbFun, void* pCBobj=NULL);
    // 获取、设置PTZ端口的回调
    void SetCB_GetEncPtzPort(GetEncPtzPortCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncPtzPort(SetEncPtzPortCB_T cbFun, void* pCBobj=NULL);
    // 获取、设置编码器报警信息的回调
    void SetCB_GetEncAlarmin(GetEncAlarminCB_T cbFun, void* pCBobj=NULL);
    void SetCB_GetEncAlarmout(GetEncAlarmoutCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncAlarm(SetEncAlarmCB_T cbFun, void* pCBobj=NULL);
    // 获取、设置通道信息的回调
    void SetCB_GetEncChannel(GetEncChannelCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncChannel(SetEncChannelCB_T cbFun, void* pCBobj=NULL);
    // 获取、设置OSD显示信息的回调
    void SetCB_GetEncDisplay(GetEncDisplayCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncDisplay(SetEncDisplayCB_T cbFun, void* pCBobj=NULL);
    // 获取、设置码流传输信息的回调
    void SetCB_GetEncTransfer(GetEncTransferCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncTransfer(SetEncTransferCB_T cbFun, void* pCBobj=NULL);
    // 获取、设置码流信息的回调
    void SetCB_GetEncVideo(GetEncVideoCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncVideo(SetEncVideoCB_T cbFun, void* pCBobj=NULL);
private:
    // 回调成员  
    static GetEncAlarminCB_T m_cbGetEncAlarmin;
    static void* m_pobjGetEncAlarmin; 
    static GetEncAlarmoutCB_T m_cbGetEncAlarmout;
    static void* m_pobjGetEncAlarmout;
    static SetEncAlarmCB_T m_cbSetEncAlarm;
    static void* m_pobjSetEncAlarm;

    static GetEncForwardportCB_T m_cbGetEncForwardport;
    static void* m_pobjGetEncForwardport;
    static SetEncForwardportCB_T m_cbSetEncForwardport;
    static void* m_pobjSetEncForwardport;

    static GetEncPtzPortCB_T m_cbGetEncPtzPort;
    static void* m_pobjGetEncPtzPort;
    static SetEncPtzPortCB_T m_cbSetEncPtzPort;
    static void* m_pobjSetEncPtzPort;

    static GetEncChannelCB_T m_cbGetEncChn;
    static void* m_pobjGetEncChn;
    static SetEncChannelCB_T m_cbSetEncChn;
    static void* m_pobjSetEncChn;

    static GetEncDisplayCB_T m_cbGetEncDsp;
    static void* m_pobjGetEncDsp;
    static SetEncDisplayCB_T m_cbSetEncDsp;
    static void* m_pobjSetEncDsp;

    static GetEncTransferCB_T m_cbGetEncTrans;
    static void* m_pobjGetEncTrans;
    static SetEncTransferCB_T m_cbSetEncTrans;
    static void* m_pobjSetEncTrans;

    static GetEncVideoCB_T m_cbGetEncVideo;
    static void* m_pobjGetEncVideo;
    static SetEncVideoCB_T m_cbSetEncVideo;
    static void* m_pobjSetEncVideo;
};

#endif // !defined(AFX_EWCONFIG_H__2D79C4D4_5C3B_4688_BB79_392D8BCA3245__INCLUDED_)
