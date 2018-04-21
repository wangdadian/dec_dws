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

    // 获取当前时间，时间格式：2013-10-10 10:10:10
    // szTime: 调用者分配64字节内存
    long GetTime(char* szTime);

    // 设置时间，时间格式：2013-10-10 10:10:10
    long SetTime(const char* szTime);
};

#endif // !defined(AFX_TIMECFG_H__AEEF7A76_9F86_4D26_9065_15ABFBE6C328__INCLUDED_)


