/************************************************************************
Copyright (C), 2011, MingDing. Co., Ltd.
Author:        
Version:        0.0.0.1
Date:           2013-10-08
Description:	dec web server

  History:                                                                
  1.Created on 2011-01-04
******************************************************************************/

#include <stdarg.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//#include <execinfo.h>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>
#include <iostream>
#include <signal.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <dlfcn.h>

using namespace std;
#include "WebSvr.h"
#include "Facility.h"
#include "define.h"

//////////////////////////////////////////////////////////////////////////
//ȫ��

// �����Ƿ��˳���ʾ
volatile bool g_bExit = false;	

/*
 * �ж�dws�Ƿ��Ѿ����У�true���У�falseδ����
 * ͨ�����ļ���д�������ж��Ƿ������С�һ���ļ�ֻ����һ��д����
*/
bool IsRun ()
{
    // ����ļ������ڣ��򴴽��ļ���Ȼ�������ļ�
    int fd_lock = 0;
    fd_lock = open(DW_LOCK_FILE, O_CREAT | O_WRONLY, 0644);
    if ( fd_lock < 0 )
    {   
        return FALSE;
    }

	flock lock;
	memset(&lock, 0, sizeof(lock));
	lock.l_type = F_WRLCK;
	int nRet = fcntl(fd_lock, F_SETLK, &lock);
	if( nRet < 0 )
	{
        int iErr = errno;
        // ����ʧ�ܣ����ѱ���������˵��dws������
		if ( iErr == EAGAIN || iErr == EACCES )
		{
            close(fd_lock);
            fprintf(stderr,  "%s has been running...\n", DW_NAME);
            return TRUE;
        }

	}
    return FALSE;
}

//////////////////////////////////////////////////////////////////////////
// main ����
int main(int argc,char **argv)
{
	CWebSvr *p_WebSvr = new CWebSvr;
    // �Ƿ�������
    if ( IsRun() == true )
    {
        return RET_FAILED;
    }

    // ��������
	p_WebSvr->init();
	while ( g_bExit == false )
	{
		CFacility::SleepMsec(2000);
	}
    delete p_WebSvr;

	return 0;
}


