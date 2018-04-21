// Device.cpp: implementation of the CDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "Device.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDevice::CDevice()
{

}

CDevice::~CDevice()
{

}

// ��ȡ�豸����ʱ��
// szUptime������������64�ֽ��ڴ�
long CDevice::GetDeviceUptime(char* szUptime)
{
    long lRet = RET_SUCCESS;
    if ( szUptime == NULL )
    {
        return RET_FAILED;
    }
    FILE* fp = fopen("/proc/uptime", "r");
    if (fp==NULL) {
        return RET_FAILED;
    }
    char szBuff[1024] = {0};
    fgets(szBuff, 1024, fp);
    fclose(fp);
    char idletime[64] = {0};
    sscanf(szBuff, "%s %s", szUptime, idletime);
    return lRet;
}

// �����豸����
long CDevice::ResetParam()
{
    long lRet = RET_FAILED;
    
    return lRet;
}

// �����豸
long CDevice::RebootDevice()
{
    //reboot(RB_AUTOBOOT);
    //�滻Ϊ���´���������
    char* szCmd = "/sbin/reboot";
    int iRet = system(szCmd);
    if(iRet != 0)
    {
        return -1;
    }
    return 0;
}

// �����豸
long CDevice::UpgradeDevice()
{
    long lRet = RET_FAILED;
    
    return lRet;
}



