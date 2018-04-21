// SysInfo.h: interface for the CSysInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSINFO_H__E5F10083_5E8A_41E5_AB5A_0F204CB6E90B__INCLUDED_)
#define AFX_SYSINFO_H__E5F10083_5E8A_41E5_AB5A_0F204CB6E90B__INCLUDED_

#include "define.h"
#include "Facility.h"
#include "dwstype.h"

class CSysInfo  
{
public:
	CSysInfo();
	~CSysInfo();

    // 获取设备型号
    // szModel: 调用者分配64字节内存
    long GetDeviceModel(char* szModel);

    // 获取设备序列号
    // szModel：调用者分配64字节内存
    long GetDeviceSN(char* szSN);

    // 获取设备主控软件版本号
    // szVer：调用者分配64字节内存
    long GetDeviceVer(char* szVer);

};

#endif // !defined(AFX_SYSINFO_H__E5F10083_5E8A_41E5_AB5A_0F204CB6E90B__INCLUDED_)


