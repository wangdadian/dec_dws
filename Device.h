// Device.h: interface for the CDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICE_H__63CD4D07_022A_4D2F_8932_1F924C1442E9__INCLUDED_)
#define AFX_DEVICE_H__63CD4D07_022A_4D2F_8932_1F924C1442E9__INCLUDED_

#include "define.h"
#include "dwstype.h"
#include "Facility.h"
#include <unistd.h>
#include <sys/reboot.h>

class CDevice  
{
public:
	CDevice();
	~CDevice();
    
    // 获取设备运行时间
    // szUptime：调用者申请64字节内存
    long GetDeviceUptime(char* szUptime);

    // 重设设备参数
    long ResetParam();

    // 重启设备
    long RebootDevice();

    // 升级设备
    long UpgradeDevice();

private:

};

#endif // !defined(AFX_DEVICE_H__63CD4D07_022A_4D2F_8932_1F924C1442E9__INCLUDED_)
