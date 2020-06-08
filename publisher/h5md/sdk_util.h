/** @file
* ����Demo.SDKʹ������
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
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
	����SDK������
*/
class HqSdkUtil
{
public:
	string m_strUser;	//�û�ID
	string m_strPass;	//����
	string m_strAppKey; //app_key
	string m_strAppSecret;//app_secret
	string m_strIp1;//��һ�������ip.
	int m_iPort1;//��һ�������port.
	string m_strIp2;//�ڶ��������ip.
	int m_iPort2;//�ڶ��������port.

	int m_iMaxNumberTest;//���ܲ���.��������

	//�ٶȲ���
	MyVelocimetryCallback m_myVelocimetryCallback;
	Velocimetry *m_velocimetry;

	bool	m_bLogin;	//��½�ɹ���ǡ�

	HsHqSdkDemo::MyMutex m_mutexCapabilityTest; //���ܲ�����

public:
	Session *m_pSession;
	SessionOptions *m_pSessionOptions;
	H5SdkCallbackImpl m_h5SdkCallbackImpl;

public:
	HqSdkUtil();

	void SetLoginStatus(bool b) { m_bLogin = b; }
	/*
		�����ٶ�
	*/
	void speed_test(void);

	/*
		sdk ��ʼ��
	*/
	bool sdk_init(void);

	/*
		sdk �ر�
	*/
	void sdk_close(void);

	/*
		IP��ַ���л�����
	*/
	void test_ip_switch(void);

	/*
		�Ͽ����Ӳ���
	*/
	void test_disconnect(void);

	/*
		������������ա�ĳֻ���롣
	*/
	void parse_snapshot_record(IRecord* record, uint64 time);

	/*
		������������ա�
	*/
	void parse_snapshot(IHsCommMessage* response, uint64 time);

	/*
		��������ʱ��
	*/
	uint32 m_crc;//�ϴ�trend���������ȡ��crc.
	void parse_trend(IHsCommMessage* response);

	/*
		���������ί�С�
	*/
	void parse_l2_order(IHsCommMessage* response, bool bLogMore);

	/*
		�������г�������Ϣ��
	*/
	void parse_market_types(IHsCommMessage* response);

	/*
		��������������Ϣ.
		�г���ʼ����֪ͨ�����ԣ����Ҫ֪ͨ�����̣߳������¶��ĵĶ�����
	*/
	void parse_server_info(IHsCommMessage* response);

	/*
		���Ļ�Ӧ.
		����������SDK���Զ�����.
	*/
	void parse_subscribe(IHsCommMessage* response);

	/*
		���ί��.���Ļ�Ӧ.
	*/
	void parse_subscribe_l2_transcation(IHsCommMessage* response);

	/*
		���ί��.���Ļ�Ӧ.
	*/
	void parse_subscribe_l2_order(IHsCommMessage* response);

	/*
		����.K�ߡ�
	*/
	void parse_k_line(IHsCommMessage* response, uint64 time);

	/*
		��2003���г��������ȡȫ����֤ȯ���롣
	*/
	void GetCodesInMarket(const char *market, list<MyProdCode>* pList, int size);

	/*
		�г�������Ϣ.����
	*/
	void test_market_type(bool bSync);

	/*
		K��.����
	*/
	void test_k_line(const char* code, const char *market, int k_num/*��������*/, bool bSync);

	/*
		���ն��ġ�
	*/
	void SubscriberAll(list<MyProdCode> *pListCodes, bool bSync, uint32 sub_type/*���ģ��˶�*/);

	/*
		���ί��.���ġ�
	*/
	void SubL2Transcation(list<MyProdCode> *pListCodes, bool bSync, uint32 sub_type/*���ģ��˶�*/);

	/*
		���ί��.���ġ�
	*/
	void SubL2Order(list<MyProdCode> *pListCodes, bool bSync, uint32 sub_type/*���ģ��˶�*/);

	/*
		���ն���.����
	*/
	void test_subscribe(list<MyProdCode> *pListCodes, bool bSync);

	/*
		���ί��.����.����
	*/
	void test_l2_transcation(list<MyProdCode> *pListCodes, bool bSync);

	/*
		���ί��.����.����
	*/
	void test_l2_order(list<MyProdCode> *pListCodes, bool bSync);

	/*
		�ǳ�����
	*/
	void test_logout(void);

	/*
		�������.����.
		pListVodes�� iBegin �� iEnd,���һ��snapshot������ͳ�ȥ�� iBegin <= i <= iEnd
	*/
	void test_snapshot(list<MyProdCode> *pListCodes, int iBegin, int iEnd, bool bSync);

	/*
		��ʱ.����.
		pListVodes�� iBegin �� iEnd,���һ��snapshot������ͳ�ȥ�� iBegin <= i <= iEnd
	*/
	void test_trend(const char *prod_code, const char *market, bool bSync);

	/*
		���ܲ���.K��
	*/
	void capability_k_line(list<MyProdCode> *pListCodes);

	/*
		���ܲ���.����
	*/
	void capability_snapshot(list<MyProdCode> *pListCodes);

	/*
		���ļ��ȡ������Ϣ.����Ӧ�ļ������ߺ���
	*/
	bool ReadConfigure(void);
	string& trim(string &s);
	bool get_line(FILE *pFile, string& line);
	string get_cfg_str(string& line);
	int get_cfg_int(string& line);
};

/*
	log: ���ܲ��Ե�ʱ�򣬲�����ʾ̫�ࡣ
*/
	#define my_log(format, ...) \
		if(!g_pMyCapabilityTest) \
		{ \
			printf(format, ##__VA_ARGS__);	\
		}
		

/*
	����.��Ʒ����
*/
class MyProdCode
{
public:
	string	prod_code;	//��Ʒ����
	string	market;		//�г�����

public:
	MyProdCode(const char *code, const char *m) : prod_code(code), market(m){}
};
/*
	���ܲ���.Item
	K�ߣ����ջ�ȡ������Ĳ�����
*/
class MyCapabilityItem
{
public:
	string	m_strProdCode;	//����.
	string	m_strMarket;		//�г�.
	uint64	m_u64OpenPx;	//��������.���ѡȡ
	uint64	m_u64LastPx;	//��������.���ѡȡ

	uint64	m_time;		//��ȡ���ݵ�ʱ��
		
public:
	MyCapabilityItem(uint64 t, const char *code, const char *m, uint64 open, uint64 last);
	string GetFullName(string& ret);
};
/*
	���ܲ���:ͬ�����첽�ķ�ʽ��ѭ������K�ߣ����գ�Ȼ���ȡ Ԥ�ڵ���Ŀ�� ���ݺ�ֹͣ����ӡ����ʱ�䣬�����ܵ�ʧ����Ŀ��
	����������������Ƿ�������ͻ���ʵ������

	��snapshotΪ��.
	num_test: 2000֧��Ʊ����
	ÿ������100֧���룬�ܹ�20�����
	m_iNumPackage: 20
	������������ܻ�ȡ20����Ӧ.
	m_iNumPackageOK + m_iNumPackageErr ��20�Σ�������β���.
	m_listGets��������л�ȡ�Ĵ���Ĳ��������2000֧������г�ʱ��������2000֧��
*/
class MyCapabilityTest
{
public:
	uint64	m_dwStartTime;	//��ʼʱ��
	int		m_iNumPackage;//���Ե������.��
	int		m_iNumPackageOK;	//��ȷ�����.����
	int		m_iNumPackageErr;//���������.����

	int		m_iNumCodes;	//���Ա걾����
	list<MyCapabilityItem> m_listGets;	//��ȡ�ı걾.������map,����ʱ��Ͳ��ǰ�˳���ˡ�
public:
	MyEvent *m_eventCapabilityTest;//ȫ���źš��ȴ��첽������ɡ�

public:
	MyCapabilityTest(int codes, int package);

	/*
		������Ϣ
	*/
	void Log();

	/*
		�յ���������
	*/
	bool GetAllPackage() { return (m_iNumPackageOK + m_iNumPackageErr == m_iNumPackage); }

	/*
		�յ�һ����ȷ����
	*/
	void PushOkItem(uint64 time, const char *code, const char *market, uint64 open_px, uint64 last_px);

	/*
		�յ�һ����ȷ����
	*/
	void PushOkPackage(uint64 time, int callback_type);

	/*
		�յ�һ����������
	*/
	void PushErrPackage(uint64 time, int callback_type);
};

/*
	���鷵�ص������ַ�����utf-8�ġ�ת��gbk,�������롣
	���ص�szGbk��Ҫdelete.
*/
int UTF82GBK(const char *szUtf8, string &szGbk);

/*
	getTickCount
*/
uint64 getTickCount64(void);

/*
	�ȴ�,�м���������� 'q',�˳������򣬵ȴ���duration(����)������
	duration == -1, ���޵ȡ�
	return true, ��� quit �ź�.
*/
bool wait_for_quit(char *txt, long duration);

extern MyCapabilityTest* g_pMyCapabilityTest; //���ܲ��� 