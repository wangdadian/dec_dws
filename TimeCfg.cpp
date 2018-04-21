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

// ��ȡ��ǰʱ�䣬ʱ���ʽ��2013-10-10 10:10:10
// szTime: �����߷���64�ֽ��ڴ�
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

// ����ʱ�䣬ʱ���ʽ��2013-10-10 10:10:10
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