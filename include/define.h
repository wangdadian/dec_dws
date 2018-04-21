/************************************************************************/
/* 描述：用于定义一些常用的常量                                         */
/************************************************************************/

#ifndef TRANSMITUTILITY_20110104
#define TRANSMITUTILITY_20110104
//////////////////////////////////////////////////////////////////////////
#include "Facility.h"

// 此进程名称
const char DW_NAME[16] =  "dws";
// 透明端口默认端口号
#define FORWARD_PORT 3032
// 工作目录
#define  DW_WORK_DIR   "/opt/dws/"
#define  DW_EXPT_DIR   "/root/dws/except/"

// 锁文件
#define DW_LOCK_FILE "/root/dws/lock_dws.info"
// 系统信息
#define CFG_FILE_SYS "/root/dws/config/sys.ini"
// 设备型号
const int DEV_MODEL_CNT = 5; // 和下方同步
const char DEV_MODELS[][80]={"MD-ENCODER","MD-HD-ENCODER","MD-DECODER", "MD-DEC-SDENC", "MD-DEC-HDENC"};
// 配置文件，写入配置分区
// 配置文件类型
#define CFG_FILE_ALL          0 // 配置参数用的全部配置文件
#define CFG_FILE_TORESET_ALL  1 // 需要重置的全部配置文件
#define CFG_FILE_TORESET_PART 2 // 需要重置的部分配置文件
// 配置文件个数，和下方列表同步个数
#define CFG_FILE_COUNT        8
// 配置参数关联的文件
#define CFG_FILE_WEB               "/root/dws/config/web.ini"
#define CFG_FILE_USER              "/root/dws/config/user.ini"
#define CFG_FILE_DECODER           "/root/dws/config/decoder.ini"
#define CFG_FILE_APPLYMAC          "/root/applymac.sh"
#define CFG_FILE_NETWORK           "/root/network.sh"
#define CFG_FILE_HOSTNAME          "/root/hostname.sh"
#define CFG_FILE_ENCODER           "/root/dws/config/encoder.ini"
#define CFG_FILE_SYS               "/root/dws/config/sys.ini"

//重置参数关联的文件
#define CFG_FILE_TORESET_WEB       "/home/root/dws/config/web.ini"
#define CFG_FILE_TORESET_USER      "/home/root/dws/config/user.ini"
#define CFG_FILE_TORESET_DECODER   "/home/root/dws/config/decoder.ini"
#define CFG_FILE_TORESET_APPLYMAC  "/home/root/applymac.sh"
#define CFG_FILE_TORESET_NETWORK   "/home/root/network.sh"
#define CFG_FILE_TORESET_HOSTNAME  "/home/root/hostname.sh"
#define CFG_FILE_TORESET_ENCODER   "/home/root/dws/config/encoder.ini"
#define CFG_FILE_TORESET_SYS       "/home/root/dws/config/sys.ini"

//打印
#define PRINT_INFO
#ifdef  PRINT_INFO
#define MYPRINTF(format,args...)  printf(format, ##args)
//#define MYPRINTF(format,args...)  {printf("%s  ", CFacility::GetCurTime());printf(format, ##args);}
#else
#define MYPRINTF(format,args...)
#endif// PRINT_INFO

//内存释放
#define PTR_DELETE(x) \
if (x != NULL ) \
{\
    delete x ; \
    x = NULL; \
}

#define PTR_FREE(x) \
if (x != NULL ) \
{\
    free(x) ; \
    x = NULL; \
}

#define PTR_DELETE_A(x) \
if (x != NULL ) \
{\
    delete[] x ; \
    x = NULL; \
}

#define PTR_DELETE_MA(x, count) \
if (x != NULL && count > 0 ) \
{\
    for ( int i = 0; i < (int)count; i++ )\
{\
    delete x[i]; \
}\
	delete[] x ; \
	x = NULL; \
}
////////////////////////////////////////////////////////////////////////

// 调试信息代码执行与否
#define DEBUG_ENABLED

#ifndef INVALID_SOCKET
#define INVALID_SOCKET          (-1)
#endif

// 返回值
#define   RET_SUCCESS 0
#define   RET_FAILED  -1

// 字符串
#define STR_FAILED  "FAILED"
#define STR_OK      "OK"

//显示接口
#define DISPLAY_UNKNOWN  0
#define DISPLAY_VGA      1
#define DISPLAY_BNC      2
#define DISPLAY_HDMI     3

//////////////////////////////////////////////////////////////////////////
// 自定义信号，使用“kill -s 信号量值 进程ID” 给进程发信号，执行相应的处理
// 打印连接状态信息到文件
#define SIG_DW_STATE SIGUSR1+56   // kill -s 66 `pidof dws`
// 通道类型
typedef enum{
CHN_UNKNOWN=0,
CHN_DECODER,
CHN_ENCODER,
CHN_ALARMIN,
CHN_ALARMOUT,
CHN_DISPMODE,
CHN_DISPVGA,
CHN_DISPBNC,
CHN_DISPHDMI,
}E_CHN_MODE;


#endif //TRANSMITUTILITY_20110104



