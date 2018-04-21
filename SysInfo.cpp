// SysInfo.cpp: implementation of the CSysInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "SysInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysInfo::CSysInfo()
{

}

CSysInfo::~CSysInfo()
{

}

// 获取设备型号
// szModel: 调用者分配64字节内存
long CSysInfo::GetDeviceModel(char* szModel)
{
    long lRet = RET_SUCCESS;
    sprintf(szModel, "%s", "DECODER");
    return lRet;
}

// 获取设备序列号
// szModel：调用者分配64字节内存
long CSysInfo::GetDeviceSN(char* szSN)
{
    long lRet = RET_SUCCESS;
    sprintf(szSN, "%s", "SN201310081024");
    return lRet;
}

// 获取设备主控软件版本号
// szVer：调用者分配64字节内存
long CSysInfo::GetDeviceVer(char* szVer)
{
    long lRet = RET_SUCCESS;
    sprintf(szVer, "%s", "1.0.0.2");
    return lRet;
}




