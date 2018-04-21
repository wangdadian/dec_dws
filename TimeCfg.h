// TimeCfg.h: interface for the CTimeCfg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMECFG_H__AEEF7A76_9F86_4D26_9065_15ABFBE6C328__INCLUDED_)
#define AFX_TIMECFG_H__AEEF7A76_9F86_4D26_9065_15ABFBE6C328__INCLUDED_

#include "define.h"
#include "Facility.h"
#include "dwstype.h"

class CTimeCfg  
{
public:
	CTimeCfg();
	~CTimeCfg();

    // ��ȡ��ǰʱ�䣬ʱ���ʽ��2013-10-10 10:10:10
    // szTime: �����߷���64�ֽ��ڴ�
    long GetTime(char* szTime);

    // ����ʱ�䣬ʱ���ʽ��2013-10-10 10:10:10
    long SetTime(const char* szTime);
};

#endif // !defined(AFX_TIMECFG_H__AEEF7A76_9F86_4D26_9065_15ABFBE6C328__INCLUDED_)


