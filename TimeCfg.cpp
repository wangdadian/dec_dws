// TimeCfg.cpp: implementation of the CTimeCfg class.
//
//////////////////////////////////////////////////////////////////////

#include "TimeCfg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimeCfg::CTimeCfg()
{

}

CTimeCfg::~CTimeCfg()
{

}

// 获取当前时间，时间格式：2013-10-10 10:10:10
// szTime: 调用者分配64字节内存
long CTimeCfg::GetTime(char* szTime)
{
    long lRet = RET_SUCCESS;
    if (szTime == NULL)
    {
        return RET_FAILED;
    }

    int iTime = time(NULL);
    sprintf(szTime, "%s", CFacility::FormatTime(iTime));

    return lRet;
}

// 设置时间，时间格式：2013-10-10 10:10:10
long CTimeCfg::SetTime(const char* szTime)
{
    long lRet = RET_FAILED;
    if (szTime == NULL || *szTime == '\0' || 
        strncmp(szTime, STR_FAILED, strlen(STR_FAILED)) == 0 )
    {
        return lRet;
    }

    char szCmd[128] = {0};
    //sprintf(szCmd, "date -s \"%s\" && hwclock -w", szTime);
    sprintf(szCmd, "date -s \"%s\"", szTime);
    system(szCmd);
    return lRet;
}