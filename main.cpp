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
//全局

// 程序是否退出标示
volatile bool g_bExit = false;	

/*
 * 判断dws是否已经运行，true运行，false未运行
 * 通过给文件加写锁，来判断是否已运行。一个文件只能有一个写锁。
*/
bool IsRun ()
{
    // 如果文件不存在，则创建文件，然后锁定文件
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
        // 加锁失败，且已被加锁。则说明dws已运行
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
// main 函数
int main(int argc,char **argv)
{
	CWebSvr *p_WebSvr = new CWebSvr;
    // 是否已运行
    if ( IsRun() == true )
    {
        return RET_FAILED;
    }

    // 启动服务
	p_WebSvr->init();
	while ( g_bExit == false )
	{
		CFacility::SleepMsec(2000);
	}
    delete p_WebSvr;

	return 0;
}


