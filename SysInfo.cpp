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

// ��ȡ�豸�ͺ�
// szModel: �����߷���64�ֽ��ڴ�
long CSysInfo::GetDeviceModel(char* szModel)
{
    long lRet = RET_SUCCESS;
    sprintf(szModel, "%s", "DECODER");
    return lRet;
}

// ��ȡ�豸���к�
// szModel�������߷���64�ֽ��ڴ�
long CSysInfo::GetDeviceSN(char* szSN)
{
    long lRet = RET_SUCCESS;
    sprintf(szSN, "%s", "SN201310081024");
    return lRet;
}

// ��ȡ�豸��������汾��
// szVer�������߷���64�ֽ��ڴ�
long CSysInfo::GetDeviceVer(char* szVer)
{
    long lRet = RET_SUCCESS;
    sprintf(szVer, "%s", "1.0.0.2");
    return lRet;
}




