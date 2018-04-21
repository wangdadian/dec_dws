#ifndef INCLUDE_DWSTYPE_H_2013
#define INCLUDE_DWSTYPE_H_2013

#pragma pack (push,1)
/*
 *	������Ϣ�ṹ��
 */
typedef struct _NetworkInfo
{
    char ip[32];//IP��ַ
    char netmask[32];//����
    char gateway[32];//����
    
}struNetworkInfo;
/*
 *	������Ϣ�ṹ��
 */
typedef struct _SipServer
{
    char ip[32];//IP��ַ
    char id[100];//���
    
}struSipServer;

/*
 *	NTP��Ϣ�ṹ��
 */
typedef struct _NtpInfo
{
    char ip[32];//NTP������IP��ַ
    int iEnable;//�Ƿ���Ч��0-��1��
    int iInterval;//Уʱ���������
}struNtpInfo;

/*
 *	�Զ�����������Ϣ�ṹ��
 */
typedef struct _ARInfo
{
    int iEnable;//�Ƿ���Ч��0-��1��
    int iType;//�Զ�����ģʽ��0-ÿ�죬1-ÿ��һ��2-ÿ�ܶ���...��7-ÿ����
    char szTime[32];//�Զ�����ʱ��
}struARInfo;


// ϵͳ��Ϣ
typedef struct _SysInfo
{
    char name[64]; //��������
    char mac[64]; // MAC��ַ
    char model[64];//�ͺ�
    char sn[64]; //���к�
    char ver[64];//���ذ汾
    char time[64]; //ϵͳ����ʱ��
}struSysInfo;

typedef struct _DisplayResolution
{
    //��ʾģʽ0-δ֪��1-VGA, 2-BNC,3-HDMI
    int displaymode;
    // ��N����ʾͨ����1��ʼ
    int displayno;
    //0-δ֪��δ����
    //1-1920*1080
    //2-800*600
    //3-1024*768
    //4-1280*1024
    //5-1366*768
    //6-1440*900
    //7-1280*800
    int resolution;
    //������ͨ���ţ���1��ʼ��0��ʾδ�󶨣�128��ʾ2x2���ͨ����129��ʾ3x3���ͨ����130��ʾ4x4���ͨ��
    int channel;
    //�Ƿ���Ч��0-��Ч��1-��
    int enabled;
}struDisplayResolution;

//����ͨ��URL��Ϣ
typedef struct _DynamicDecUrl
{
	int fps;
    int channel; //��1��ʼ
    char url[256];
}struDynamicDecUrl;

//����ͨ����Ϣ
typedef struct _DecChannelInfo
{
    int channel; //��1��ʼ
    char code[256];
}struDecChannelInfo;

typedef struct _UserLocation
{
    char ip[32];	//��¼�û���IP
    char user[32];  //�û���
    int flag;		//��¼�û���Ȩ��
}TuserLocation;


typedef struct _UserInfo
{
    char name[32];  //�û���
    char pass[32]; //����
    long flag;		//��¼�û���Ȩ��-1-��ʾ��Ч��0-���Ȩ�޹���Ա��1-����Ա��2-��ͨ�û�
}struUserInfo;

typedef struct _DecOsdInfo
{
    char text[64];  //osd�ַ���
    //long chno;		//ͨ����
    int show;//1-��ʾ��0-����ʾ
    
}struDecOsdInfo;

#pragma pack(pop)

typedef  int                 INT32;
typedef  unsigned int        UINT32;
typedef  unsigned long long  UINT64;
typedef  long long           INT64;

#endif //INCLUDE_DWSTYPE_H_2013

