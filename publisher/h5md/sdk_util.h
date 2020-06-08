/** @file
* 行情Demo.SDK使用例子
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/
#pragma once

#include <list>
#include <string>
using namespace std;
#include "h5sdk/h5sdk.h"
#include "../MyUtil/MyEvent.h"
#include "../MyUtil/MyThread.h"
#include "sdk_callback.h"
using namespace HsHqSdkDemo;

class MyProdCode;
/*
	行情SDK工具类
*/
class HqSdkUtil
{
public:
	string m_strUser;	//用户ID
	string m_strPass;	//密码
	string m_strAppKey; //app_key
	string m_strAppSecret;//app_secret
	string m_strIp1;//第一组服务器ip.
	int m_iPort1;//第一组服务器port.
	string m_strIp2;//第二组服务器ip.
	int m_iPort2;//第二组服务器port.

	int m_iMaxNumberTest;//性能测试.代码数量

	//速度测试
	MyVelocimetryCallback m_myVelocimetryCallback;
	Velocimetry *m_velocimetry;

	bool	m_bLogin;	//登陆成功标记。

	HsHqSdkDemo::MyMutex m_mutexCapabilityTest; //性能测试锁

public:
	Session *m_pSession;
	SessionOptions *m_pSessionOptions;
	H5SdkCallbackImpl m_h5SdkCallbackImpl;

public:
	HqSdkUtil();

	void SetLoginStatus(bool b) { m_bLogin = b; }
	/*
		测试速度
	*/
	void speed_test(void);

	/*
		sdk 初始化
	*/
	bool sdk_init(void);

	/*
		sdk 关闭
	*/
	void sdk_close(void);

	/*
		IP地址和切换测试
	*/
	void test_ip_switch(void);

	/*
		断开连接测试
	*/
	void test_disconnect(void);

	/*
		解析。行情快照。某只代码。
	*/
	void parse_snapshot_record(IRecord* record, uint64 time);

	/*
		解析。行情快照。
	*/
	void parse_snapshot(IHsCommMessage* response, uint64 time);

	/*
		解析。分时。
	*/
	uint32 m_crc;//上次trend，解析后获取的crc.
	void parse_trend(IHsCommMessage* response);

	/*
		解析。逐笔委托。
	*/
	void parse_l2_order(IHsCommMessage* response, bool bLogMore);

	/*
		解析。市场分类信息。
	*/
	void parse_market_types(IHsCommMessage* response);

	/*
		解析。服务器信息.
		市场初始化，通知。所以，这里，要通知其他线程，做重新订阅的动作。
	*/
	void parse_server_info(IHsCommMessage* response);

	/*
		订阅回应.
		断线重连，SDK会自动订阅.
	*/
	void parse_subscribe(IHsCommMessage* response);

	/*
		逐笔委托.订阅回应.
	*/
	void parse_subscribe_l2_transcation(IHsCommMessage* response);

	/*
		逐笔委托.订阅回应.
	*/
	void parse_subscribe_l2_order(IHsCommMessage* response);

	/*
		解析.K线。
	*/
	void parse_k_line(IHsCommMessage* response, uint64 time);

	/*
		从2003，市场代码表，获取全部的证券代码。
	*/
	void GetCodesInMarket(const char *market, list<MyProdCode>* pList, int size);

	/*
		市场分类信息.测试
	*/
	void test_market_type(bool bSync);

	/*
		K线.测试
	*/
	void test_k_line(const char* code, const char *market, int k_num/*几个柱子*/, bool bSync);

	/*
		快照订阅。
	*/
	void SubscriberAll(list<MyProdCode> *pListCodes, bool bSync, uint32 sub_type/*订阅，退订*/);

	/*
		逐笔委托.订阅。
	*/
	void SubL2Transcation(list<MyProdCode> *pListCodes, bool bSync, uint32 sub_type/*订阅，退订*/);

	/*
		逐笔委托.订阅。
	*/
	void SubL2Order(list<MyProdCode> *pListCodes, bool bSync, uint32 sub_type/*订阅，退订*/);

	/*
		快照订阅.测试
	*/
	void test_subscribe(list<MyProdCode> *pListCodes, bool bSync);

	/*
		逐笔委托.订阅.测试
	*/
	void test_l2_transcation(list<MyProdCode> *pListCodes, bool bSync);

	/*
		逐笔委托.订阅.测试
	*/
	void test_l2_order(list<MyProdCode> *pListCodes, bool bSync);

	/*
		登出测试
	*/
	void test_logout(void);

	/*
		行情快照.测试.
		pListVodes的 iBegin 到 iEnd,组成一个snapshot命令，发送出去。 iBegin <= i <= iEnd
	*/
	void test_snapshot(list<MyProdCode> *pListCodes, int iBegin, int iEnd, bool bSync);

	/*
		分时.测试.
		pListVodes的 iBegin 到 iEnd,组成一个snapshot命令，发送出去。 iBegin <= i <= iEnd
	*/
	void test_trend(const char *prod_code, const char *market, bool bSync);

	/*
		性能测试.K线
	*/
	void capability_k_line(list<MyProdCode> *pListCodes);

	/*
		性能测试.快照
	*/
	void capability_snapshot(list<MyProdCode> *pListCodes);

	/*
		从文件里，取配置信息.及相应的几个工具函数
	*/
	bool ReadConfigure(void);
	string& trim(string &s);
	bool get_line(FILE *pFile, string& line);
	string get_cfg_str(string& line);
	int get_cfg_int(string& line);
};

/*
	log: 性能测试的时候，不能提示太多。
*/
	#define my_log(format, ...) \
		if(!g_pMyCapabilityTest) \
		{ \
			printf(format, ##__VA_ARGS__);	\
		}
		

/*
	测试.产品代码
*/
class MyProdCode
{
public:
	string	prod_code;	//产品代码
	string	market;		//市场代码

public:
	MyProdCode(const char *code, const char *m) : prod_code(code), market(m){}
};
/*
	性能测试.Item
	K线，快照获取后，填入的参数。
*/
class MyCapabilityItem
{
public:
	string	m_strProdCode;	//代码.
	string	m_strMarket;		//市场.
	uint64	m_u64OpenPx;	//特征参数.随机选取
	uint64	m_u64LastPx;	//特征参数.随机选取

	uint64	m_time;		//获取数据的时间
		
public:
	MyCapabilityItem(uint64 t, const char *code, const char *m, uint64 open, uint64 last);
	string GetFullName(string& ret);
};
/*
	性能测试:同步，异步的方式，循环调用K线，快照，然后获取 预期的数目的 数据后，停止，打印所耗时间，及可能的失败数目。
	测试行情服务器，是否能满足客户的实际需求。

	以snapshot为例.
	num_test: 2000支股票代码
	每个命令100支代码，总共20个命令。
	m_iNumPackage: 20
	命令发出后，期望能获取20次响应.
	m_iNumPackageOK + m_iNumPackageErr 到20次，结束这次测试.
	m_listGets里，包含所有获取的代码的采样。最多2000支。如果有超时，就少于2000支。
*/
class MyCapabilityTest
{
public:
	uint64	m_dwStartTime;	//开始时间
	int		m_iNumPackage;//测试的命令包.数
	int		m_iNumPackageOK;	//正确命令包.数。
	int		m_iNumPackageErr;//错误命令包.数。

	int		m_iNumCodes;	//测试标本数。
	list<MyCapabilityItem> m_listGets;	//获取的标本.不能用map,否则，时间就不是按顺序了。
public:
	MyEvent *m_eventCapabilityTest;//全局信号。等待异步动作完成。

public:
	MyCapabilityTest(int codes, int package);

	/*
		调试信息
	*/
	void Log();

	/*
		收到所有命令
	*/
	bool GetAllPackage() { return (m_iNumPackageOK + m_iNumPackageErr == m_iNumPackage); }

	/*
		收到一个正确代码
	*/
	void PushOkItem(uint64 time, const char *code, const char *market, uint64 open_px, uint64 last_px);

	/*
		收到一个正确命令
	*/
	void PushOkPackage(uint64 time, int callback_type);

	/*
		收到一个错误命令
	*/
	void PushErrPackage(uint64 time, int callback_type);
};

/*
	行情返回的中文字符，是utf-8的。转成gbk,否则乱码。
	返回的szGbk需要delete.
*/
int UTF82GBK(const char *szUtf8, string &szGbk);

/*
	getTickCount
*/
uint64 getTickCount64(void);

/*
	等待,中间如果有输入 'q',退出。否则，等待到duration(毫秒)。有误差。
	duration == -1, 无限等。
	return true, 获得 quit 信号.
*/
bool wait_for_quit(char *txt, long duration);

extern MyCapabilityTest* g_pMyCapabilityTest; //性能测试 