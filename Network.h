// Network.h: interface for the CNetwork class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETWORK_H__83B18AFC_D50D_4864_B824_6F57DEECE936__INCLUDED_)
#define AFX_NETWORK_H__83B18AFC_D50D_4864_B824_6F57DEECE936__INCLUDED_

#include "define.h"
#include "Facility.h"
#include "dwstype.h"

class CNetwork  
{
public:
	CNetwork();
	~CNetwork();
    // 设置网络信息
    long SetNetworkInfo(const struNetworkInfo *pNI);
    // 获取网络信息
    long GetNetworkInfo(struNetworkInfo* pNI);

};

#endif // !defined(AFX_NETWORK_H__83B18AFC_D50D_4864_B824_6F57DEECE936__INCLUDED_)


