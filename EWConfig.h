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

// ��������
// ���á���ȡ͸���˿���Ϣ
typedef long (*GetEncForwardportCB_T)(char* szBuf, void* param);
typedef long (*SetEncForwardportCB_T)(const char* szBuf, void* param);
// ���á���ȡPtz�˿���Ϣ
typedef long (*GetEncPtzPortCB_T)(char* szBuf, void* param);
typedef long (*SetEncPtzPortCB_T)(const char* szBuf, void* param);
// ���á���ȡ������Ϣ
typedef long (*GetEncAlarminCB_T)(char* szBuf, int no, void* param);
typedef long (*GetEncAlarmoutCB_T)(char* szBuf, int no, void* param);
typedef long (*SetEncAlarmCB_T)(const char* szBuf, void* param);
// ���á���ȡͨ����Ϣ
typedef long (*GetEncChannelCB_T)(char* szBuf, int chnno, void* param);
typedef long (*SetEncChannelCB_T)(const char* szBuf, void* param);
// ���á���ȡOSD��ʾ
typedef long (*GetEncDisplayCB_T)(char* szBuf, int chnno, void* param);
typedef long (*SetEncDisplayCB_T)(const char* szBuf, void* param);
// ��ȡ�����ñ���ͨ������������Ϣ
typedef long (*GetEncTransferCB_T)(char* szBuf, int chnno, void* param);
typedef long (*SetEncTransferCB_T)(const char* szBuf, void* param);
// ��ȡ�����ñ���ͨ��������Ϣ
typedef long (*GetEncVideoCB_T)(char* szBuf, int chnno, void* param);
typedef long (*SetEncVideoCB_T)(const char* szBuf, void* param);

class CEWConfig  
{
public:
	CEWConfig();
	virtual ~CEWConfig();

    //////////////////////////////////////////////////////////////////////////
    // ��ȡ�����ñ�����͸���˿���Ϣ
    long GetEncForwardport(char* szBuf);
    long SetEncForwardport(const char* szBuf);
    // ��ȡ�����ñ�����PTZ���ƶ˿���Ϣ
    long GetEncPtzPort(char* szBuf);
    long SetEncPtzPort(const char* szBuf);
    
    // ��ȡ�����ñ�����ͨ����Ϣ
    long GetEncChannel(char* szBuf, int chnno);
    long SetEncChannel(const char* szBuf);

    // ��ȡ�����ñ�����ͨ����ʾ��Ϣ
    long GetEncDisplay(char* szBuf, int chnno);
    long SetEncDisplay(const char* szBuf);

    // ��ȡ�����ñ�����ͨ������������Ϣ
    long GetEncTransfer(char* szBuf, int chnno);
    long SetEncTransfer(const char* szBuf);

    // ��ȡ�����ñ�����ͨ��������Ϣ
    long GetEncVideo(char* szBuf, int chnno);
    long SetEncVideo(const char* szBuf);

    // ��ȡ�����ñ�����������Ϣ
    long GetEncAlarmin(char* szBuf, int no);
    long GetEncAlarmout(char* szBuf, int no);
    long SetEncAlarm(const char* szBuf);
    //////////////////////////////////////////////////////////////////////////
    // ���ûص�����
    // ��ȡ������͸���˿ڵĻص�
    void SetCB_GetEncForwardport(GetEncPtzPortCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncForwardport(SetEncPtzPortCB_T cbFun, void* pCBobj=NULL);
    // ��ȡ������PTZ�˿ڵĻص�
    void SetCB_GetEncPtzPort(GetEncPtzPortCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncPtzPort(SetEncPtzPortCB_T cbFun, void* pCBobj=NULL);
    // ��ȡ�����ñ�����������Ϣ�Ļص�
    void SetCB_GetEncAlarmin(GetEncAlarminCB_T cbFun, void* pCBobj=NULL);
    void SetCB_GetEncAlarmout(GetEncAlarmoutCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncAlarm(SetEncAlarmCB_T cbFun, void* pCBobj=NULL);
    // ��ȡ������ͨ����Ϣ�Ļص�
    void SetCB_GetEncChannel(GetEncChannelCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncChannel(SetEncChannelCB_T cbFun, void* pCBobj=NULL);
    // ��ȡ������OSD��ʾ��Ϣ�Ļص�
    void SetCB_GetEncDisplay(GetEncDisplayCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncDisplay(SetEncDisplayCB_T cbFun, void* pCBobj=NULL);
    // ��ȡ����������������Ϣ�Ļص�
    void SetCB_GetEncTransfer(GetEncTransferCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncTransfer(SetEncTransferCB_T cbFun, void* pCBobj=NULL);
    // ��ȡ������������Ϣ�Ļص�
    void SetCB_GetEncVideo(GetEncVideoCB_T cbFun, void* pCBobj=NULL);
    void SetCB_SetEncVideo(SetEncVideoCB_T cbFun, void* pCBobj=NULL);
private:
    // �ص���Ա  
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
