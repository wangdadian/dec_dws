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

// 获取设备运行时间
// szUptime：调用者申请64字节内存
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

// 重设设备参数
long CDevice::ResetParam()
{
    long lRet = RET_FAILED;
    
    return lRet;
}

// 重启设备
long CDevice::RebootDevice()
{
    //reboot(RB_AUTOBOOT);
    //替换为以下代码重启：
    char* szCmd = "/sbin/reboot";
    int iRet = system(szCmd);
    if(iRet != 0)
    {
        return -1;
    }
    return 0;
}

// 升级设备
long CDevice::UpgradeDevice()
{
    long lRet = RET_FAILED;
    
    return lRet;
}



