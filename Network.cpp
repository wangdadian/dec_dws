// Network.cpp: implementation of the CNetwork class.
//
//////////////////////////////////////////////////////////////////////

#include "Network.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetwork::CNetwork()
{

}

CNetwork::~CNetwork()
{

}

// 设置网络信息
long CNetwork::SetNetworkInfo(const struNetworkInfo *pNI)
{
    long lRet = RET_FAILED;
    if ( pNI == NULL ) 
    {
        return lRet;
    }
    
    return lRet;
}

// 获取网络信息
long CNetwork::GetNetworkInfo(struNetworkInfo* pNI)
{
    long lRet = RET_FAILED;
    if ( pNI == NULL ) 
    {
        return lRet;
    }

    return lRet;
}


