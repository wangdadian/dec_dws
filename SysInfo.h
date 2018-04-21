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

    // ��ȡ�豸�ͺ�
    // szModel: �����߷���64�ֽ��ڴ�
    long GetDeviceModel(char* szModel);

    // ��ȡ�豸���к�
    // szModel�������߷���64�ֽ��ڴ�
    long GetDeviceSN(char* szSN);

    // ��ȡ�豸��������汾��
    // szVer�������߷���64�ֽ��ڴ�
    long GetDeviceVer(char* szVer);

};

#endif // !defined(AFX_SYSINFO_H__E5F10083_5E8A_41E5_AB5A_0F204CB6E90B__INCLUDED_)


