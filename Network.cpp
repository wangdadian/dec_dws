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

// ����������Ϣ
long CNetwork::SetNetworkInfo(const struNetworkInfo *pNI)
{
    long lRet = RET_FAILED;
    if ( pNI == NULL ) 
    {
        return lRet;
    }
    
    return lRet;
}

// ��ȡ������Ϣ
long CNetwork::GetNetworkInfo(struNetworkInfo* pNI)
{
    long lRet = RET_FAILED;
    if ( pNI == NULL ) 
    {
        return lRet;
    }

    return lRet;
}


