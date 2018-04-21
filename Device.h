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
    
    // ��ȡ�豸����ʱ��
    // szUptime������������64�ֽ��ڴ�
    long GetDeviceUptime(char* szUptime);

    // �����豸����
    long ResetParam();

    // �����豸
    long RebootDevice();

    // �����豸
    long UpgradeDevice();

private:

};

#endif // !defined(AFX_DEVICE_H__63CD4D07_022A_4D2F_8932_1F924C1442E9__INCLUDED_)
