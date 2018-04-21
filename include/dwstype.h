#ifndef INCLUDE_DWSTYPE_H_2013
#define INCLUDE_DWSTYPE_H_2013

#pragma pack (push,1)
/*
 *	网络信息结构体
 */
typedef struct _NetworkInfo
{
    char ip[32];//IP地址
    char netmask[32];//掩码
    char gateway[32];//网关
    
}struNetworkInfo;
/*
 *	网络信息结构体
 */
typedef struct _SipServer
{
    char ip[32];//IP地址
    char id[100];//编号
    
}struSipServer;

/*
 *	NTP信息结构体
 */
typedef struct _NtpInfo
{
    char ip[32];//NTP服务器IP地址
    int iEnable;//是否生效，0-否，1是
    int iInterval;//校时间隔，分钟
}struNtpInfo;

/*
 *	自动重启设置信息结构体
 */
typedef struct _ARInfo
{
    int iEnable;//是否生效，0-否，1是
    int iType;//自动重启模式，0-每天，1-每周一，2-每周二，...，7-每周日
    char szTime[32];//自动重启时间
}struARInfo;


// 系统信息
typedef struct _SysInfo
{
    char name[64]; //主机名称
    char mac[64]; // MAC地址
    char model[64];//型号
    char sn[64]; //序列号
    char ver[64];//主控版本
    char time[64]; //系统更新时间
}struSysInfo;

typedef struct _DisplayResolution
{
    //显示模式0-未知，1-VGA, 2-BNC,3-HDMI
    int displaymode;
    // 第N个显示通道，1开始
    int displayno;
    //0-未知、未设置
    //1-1920*1080
    //2-800*600
    //3-1024*768
    //4-1280*1024
    //5-1366*768
    //6-1440*900
    //7-1280*800
    int resolution;
    //关联的通道号，从1开始，0表示未绑定，128表示2x2组合通道，129表示3x3组合通道，130表示4x4组合通道
    int channel;
    //是否生效，0-生效，1-否
    int enabled;
}struDisplayResolution;

//解码通道URL信息
typedef struct _DynamicDecUrl
{
	int fps;
    int channel; //从1开始
    char url[256];
}struDynamicDecUrl;

//解码通道信息
typedef struct _DecChannelInfo
{
    int channel; //从1开始
    char code[256];
}struDecChannelInfo;

typedef struct _UserLocation
{
    char ip[32];	//登录用户的IP
    char user[32];  //用户名
    int flag;		//登录用户的权限
}TuserLocation;


typedef struct _UserInfo
{
    char name[32];  //用户名
    char pass[32]; //密码
    long flag;		//登录用户的权限-1-表示无效，0-最高权限管理员，1-操作员，2-普通用户
}struUserInfo;

typedef struct _DecOsdInfo
{
    char text[64];  //osd字符串
    //long chno;		//通道号
    int show;//1-显示，0-不显示
    
}struDecOsdInfo;

#pragma pack(pop)

typedef  int                 INT32;
typedef  unsigned int        UINT32;
typedef  unsigned long long  UINT64;
typedef  long long           INT64;

#endif //INCLUDE_DWSTYPE_H_2013

