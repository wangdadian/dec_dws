/************************************************************************/
/* ���������ڶ���һЩ���õĳ���                                         */
/************************************************************************/

#ifndef TRANSMITUTILITY_20110104
#define TRANSMITUTILITY_20110104
//////////////////////////////////////////////////////////////////////////
#include "Facility.h"

// �˽�������
const char DW_NAME[16] =  "dws";
// ͸���˿�Ĭ�϶˿ں�
#define FORWARD_PORT 3032
// ����Ŀ¼
#define  DW_WORK_DIR   "/opt/dws/"
#define  DW_EXPT_DIR   "/root/dws/except/"

// ���ļ�
#define DW_LOCK_FILE "/root/dws/lock_dws.info"
// ϵͳ��Ϣ
#define CFG_FILE_SYS "/root/dws/config/sys.ini"
// �豸�ͺ�
const int DEV_MODEL_CNT = 5; // ���·�ͬ��
const char DEV_MODELS[][80]={"MD-ENCODER","MD-HD-ENCODER","MD-DECODER", "MD-DEC-SDENC", "MD-DEC-HDENC"};
// �����ļ���д�����÷���
// �����ļ�����
#define CFG_FILE_ALL          0 // ���ò����õ�ȫ�������ļ�
#define CFG_FILE_TORESET_ALL  1 // ��Ҫ���õ�ȫ�������ļ�
#define CFG_FILE_TORESET_PART 2 // ��Ҫ���õĲ��������ļ�
// �����ļ����������·��б�ͬ������
#define CFG_FILE_COUNT        8
// ���ò����������ļ�
#define CFG_FILE_WEB               "/root/dws/config/web.ini"
#define CFG_FILE_USER              "/root/dws/config/user.ini"
#define CFG_FILE_DECODER           "/root/dws/config/decoder.ini"
#define CFG_FILE_APPLYMAC          "/root/applymac.sh"
#define CFG_FILE_NETWORK           "/root/network.sh"
#define CFG_FILE_HOSTNAME          "/root/hostname.sh"
#define CFG_FILE_ENCODER           "/root/dws/config/encoder.ini"
#define CFG_FILE_SYS               "/root/dws/config/sys.ini"

//���ò����������ļ�
#define CFG_FILE_TORESET_WEB       "/home/root/dws/config/web.ini"
#define CFG_FILE_TORESET_USER      "/home/root/dws/config/user.ini"
#define CFG_FILE_TORESET_DECODER   "/home/root/dws/config/decoder.ini"
#define CFG_FILE_TORESET_APPLYMAC  "/home/root/applymac.sh"
#define CFG_FILE_TORESET_NETWORK   "/home/root/network.sh"
#define CFG_FILE_TORESET_HOSTNAME  "/home/root/hostname.sh"
#define CFG_FILE_TORESET_ENCODER   "/home/root/dws/config/encoder.ini"
#define CFG_FILE_TORESET_SYS       "/home/root/dws/config/sys.ini"

//��ӡ
#define PRINT_INFO
#ifdef  PRINT_INFO
#define MYPRINTF(format,args...)  printf(format, ##args)
//#define MYPRINTF(format,args...)  {printf("%s  ", CFacility::GetCurTime());printf(format, ##args);}
#else
#define MYPRINTF(format,args...)
#endif// PRINT_INFO

//�ڴ��ͷ�
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

// ������Ϣ����ִ�����
#define DEBUG_ENABLED

#ifndef INVALID_SOCKET
#define INVALID_SOCKET          (-1)
#endif

// ����ֵ
#define   RET_SUCCESS 0
#define   RET_FAILED  -1

// �ַ���
#define STR_FAILED  "FAILED"
#define STR_OK      "OK"

//��ʾ�ӿ�
#define DISPLAY_UNKNOWN  0
#define DISPLAY_VGA      1
#define DISPLAY_BNC      2
#define DISPLAY_HDMI     3

//////////////////////////////////////////////////////////////////////////
// �Զ����źţ�ʹ�á�kill -s �ź���ֵ ����ID�� �����̷��źţ�ִ����Ӧ�Ĵ���
// ��ӡ����״̬��Ϣ���ļ�
#define SIG_DW_STATE SIGUSR1+56   // kill -s 66 `pidof dws`
// ͨ������
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



