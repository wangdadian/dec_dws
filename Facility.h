/************************************************************************/
/* Added by wangdd, 2011-01-04 15:00
   Description: ���õĹ��ߺ���
*/
/************************************************************************/

#ifndef FACILITY_H_20110104
#define FACILITY_H_20110104

#include <time.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <unistd.h>
#include <linux/hdreg.h>
#include <ctype.h>
#include <netinet/in.h>
#include <sys/param.h>
using namespace std;

//////////////////////////////////////////////////////////////////////////
#define MAXINTERFACES 8
class CFacility
{
public:
    
    enum NetInfoType
    {
        NetInfoType_MAC = 0x00,
            NetInfoType_IP = 0x01,
            
    };

    /* ���ܣ���ȡϵͳ��ǰʱ�� */
    // ���أ���ʽ�硰2008-07-31 11:00:00:666���ĵ�ǰϵͳ�ַ���
    static char* GetCurTime();


    /* ���ܣ���ʽ��ʱ�䡰2008-07-31 11:00:00�� */
    // ���룺iTime��ͨ��time(NULL)���غ��ʱ��ֵ
    // ���أ����ظ�ʽ�����ʱ��
    static char* FormatTime(int iTime);

    /* ���ܣ���ʽ��ʱ�䡰2008-07-31 11:00:00��Ϊ���� */
    // ���룺szTime�����ơ�2008-07-31 11:00:00��
    // ���أ����ظ�ʽ�����ʱ��
    static int FormatTime(const char *szTime);


    /* ���ܣ������ļ��� */
    // ���룺szPath���ļ��еľ���·��
    // ���أ��ɹ�����0��ʧ�ܷ���-1
    static int CreateDir(const char* szPath);

    /*�ж��Ƿ�ΪIP ��ַ*/
    static bool bIpAddress(const char* szIp);

    // �ж��Ƿ���MAC��ַ
    static bool bMAC(const char* szMAC);

    // ��ȡIP��ַ,ip-��������������ȡ��IP��ַ��32�ֽ�
    static void GetIP(char *ip);
    // ��ȡMAC��ַ
    static void GetMAC(unsigned char* mac);
    /*
        ����socketΪ������ģʽ
    */
    static int SetNonBlocking(int sock);
    /*
        ˯�ߣ�΢�뼶�����뼶���뼶
    */
    static void SleepUsec(unsigned int ustime); // usec
    static void SleepMsec(unsigned int mstime); // ms
    static void SleepSec(unsigned int stime);   // sec

    /*
        ��ʼ��Ϊ�ػ�����
    */
    static int BeDaemon(const char* szCmd);
private:
    static int GetLocalNetInfo( struct ifreq *buf, enum NetInfoType iType );
};

//////////////////////////////////////////////////////////////////////////

#endif // FACILITY_H_20110104



