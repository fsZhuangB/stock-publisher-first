///���������ӿڶ���
/*******************************************************
  Դ��������:plugin_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ���������ӿڱ�׼
  ģ������:  ����ģ��
  ����˵��: �����ͨ�ýӿڶ���
 *1��������Կ����Ը���ΪĿ�ģ��Զ�̬�⣨����⣩����ʽ��װ��������Թ��ܵ�ʵ�֣�ͳһ���嶯̬�������淶��<p>
 *2�����������װ�ķ���һ����ͨ�õġ������ġ���ҵ��Ĺ��ܣ������һ��������һ��IoC�Ĳ�������У�Ҳ����������������ʹ�ã�<p>
 *3������ӿڶ������C++������࣬����IKnown�ӿڼ̳У�IKnown�ӿ��е�QueryInterface���������Ի�ø÷���ķ�ת���ƽӿ�IIoC�����߹���ӿ�IManged��<p>
 *   ��ת���ƽӿ�IIoC�������ø÷���ʵ������Ҫ���������������Ϣ�������Ļ�������������ӿڣ�<p>
 *   ���߹���ӿ�IManged����ʵ�ֶԸ÷����������ʱ�����߼�������<p>
 *4��Ϊ�˱��ڿ����Ը��ã��Խӿڶ����������޶���<p>
 *   ���ӿں�����ʹ�õĲ��������޶�ΪC++�����������ͣ�int��char��char *��void *��double��<p>
 *   �ӿں������������أ�<p>
             
  ��    ��:  �з�����
  ��������:  20071229
  ��    ע:  ��windows��ע�⺯�����÷�ʽ��__stdcall

  �޸����ڣ�20080310
  �޸���Ա��zhangly
  �޸�˵��������20080305����������һЩͬ���������ӿ��ϣ����Ӵ���������һ������ʱ�Ļص����� PFOnSetTimeOut

  �޸����ڣ�20080124
  �޸���Ա��zhangly
  �޸�˵�����޸��˲������������ԭ�Ͷ���,��֧�ֶ�ʵ��.PFgetxxxxDependService(),PFinitxxxx()���������Ӵ���һ��ʵ��ָ��

  �޸����ڣ�20080116
  �޸���Ա��zhangly
  �޸�˵����config.h�޸�����ض���,��IConfigObject��ΪIRCfgObj

  �޸����ڣ�20080111
  �޸���Ա��zhangly
  �޸�˵��������20080110���������޸�IIoC�ӿ�,PFgetxxxxDependService����
  
  �޸����ڣ�20080623
  �޸���Ա��liangyong
  �޸�˵�����޸�ҵ��������ӿ�����, IPacker --> IF2Packer
  									IUnPacker --> IF2UnPacker
*********************************************************/

#ifndef PluginInterface_h
#define PluginInterface_h
#include <Include/pluginid.h>
#include <stdio.h>

#ifdef _WIN32
	#if !defined( FUNCTION_CALL_MODE )
	#define FUNCTION_CALL_MODE		__stdcall
	#endif
#else
	#define FUNCTION_CALL_MODE
#endif

///PFgetxxxxInfo()����I_OK��ʾ�������鵽��������
#define I_OK 1
///PFgetxxxxInfo()����I_NONE��ʾ�������鲻����������
#define I_NONE 0

///�ӿ�Ψһ��ʶ�����ͣ��ɼ��ܰ�ͳһ������������"com.hundsun.fbase.log" ����˾��.��ĿӢ�ļ��.�ӿ�����
#define HS_SID  const char *

///��ת�������ӿ�ID
#define SID_IOC  "com.hundsun.fbase.IoC"
///�������ӿ�ID
#define SID_MANAGER  "com.hundsun.fbase.Manager"

#ifndef HS_IKNOWN
#define HS_IKNOWN

///����ӿ�ͳһ�Ĳ�ѯ�����ýӿڣ����в���ṩ�Ľӿڶ�Ҫʵ�� IKnown (����COM��׼)
struct IKnown
{
	///�ӿڲ�ѯ
	/**��ѯ�뵱ǰ�ӿ���ص������ӿڣ�������Բ鵽 IIoC, IManager ��
	 *@param HS_SID  iid  �ӿ�ȫ��Ψһ��ʶ
	 *@param IKnown **ppv ����iid��Ӧ�Ľӿ�ָ��
	 *@return I_OK �ɹ���I_NONE δ�鵽iid ��Ӧ�ӿ�
	 */
    virtual unsigned long  FUNCTION_CALL_MODE QueryInterface( HS_SID iid, IKnown **ppv ) = 0;
	///���ýӿڣ����ü�����һ(���߳�����ʱ������ʵ�ִ�����Ҫ�Լ���ֵ�������޸�)
    virtual unsigned long  FUNCTION_CALL_MODE AddRef() = 0;
	///�ͷŽӿڣ����ü�����һ������Ϊ0ʱ�ͷŽӿڵ�ʵ�ֶ���(���߳�����ʱ������ʵ�ִ�����Ҫ�Լ���ֵ�����������޸�)
    virtual unsigned long  FUNCTION_CALL_MODE Release() =  0;
};


struct IRCfgObj; //��״���ö���ӿڣ�����XML��ͨ���˽ӿڿɱ�����������


/*
//���������ڵ�
#define CO_PLUGIN "plugin"

//����������ڵ�
#define CO_PUB  "pub"


//����б�������ڵ�
#define CO_PLUGINS "plugins"

*/





//���������ڵ�
#define CO_PLUGIN "plugin"

//����������ڵ�
#define CO_PUB  "pub"

//ESB����Ĺ���������ڵ��µ�Ӧ����Ϣ�ӽڵ㼰����
//@{
//������������AppInfo�ӽڵ㣬��ΪESBÿ���������߼��ϵ�Ψһ��ʶ
#define CO_APP_INFO  "AppInfo"
//������������AppInfo�ӽڵ㣬Ӧ����(����)����
#define CO_ATTR_APP_NAME  "AppName"
//������������AppInfo�ӽڵ㣬Ӧ�ñ��(���ڱ��)���ԣ�һ���������в���ָ��
#define CO_ATTR_APP_ID  "AppID"
//������������AppInfo�ӽڵ㣬�������������(�߼��ϵķ�����)
#define CO_ATTR_SVR_NAME  "SvrName"
//������������AppInfo�ӽڵ㣬������̱�����ԣ�ͬһ�ַ��������Ϊfork�����ж������ʱ��ÿ��������һ�����
#define CO_ATTR_SVR_ID  "SvrID"
//������������Args�ӽڵ㣬�洢�����������������洢��ʽ���£�
//<Args opt="value"> optΪ��������valueΪ����ֵ��(��ֵ��������¼������)
//�磺hsserver -start monsvr -s 1 -c��Ϊ<Args Exe="hsserver" start="monsvr" s="1">
#define CO_APP_ARGS  "Args"
//hsserver��Ӧ�ó�����, ��Args�е�Exe
#define CO_APP_ARGS_EXE "Exe"
//@}

//����б�������ڵ�
#define CO_PLUGINS "block"


///�����ת���ƽӿڣ�ͨ���˽ӿ�������Ӧ�ã���ò������������������Ϣ:������Ϣ(�����в�����ͬ��������Ϣ)����������������ӿڣ�
/**
 *����ҪΪ������������ͨ�����ʵ�ֵ�IKnown�ӿ��е�QueryInterface(SID_IOC,&lpIoC)�����Ի�ñ��ӿڣ�<p>
 *һ����������ͨ���˽ӿ�Ϊ�����������������û�ж���������,����Բ��ṩ�˽ӿڣ�
 */
struct IIoC : IKnown
{

	///����������Ϣ
    /**ע�������л��������ö���������ڣ�һ�����ϵͳ����ʱ�ͽ���������ռ���ڴ�.
	 *@param const char * sPath  ���ö���·����ʶ���Ϸ�ȡֵ�� "pub"     �������ö���,�������в���
	                                                          "plugin"  ��ǰ��������ö���
                                                              "plugins" ����б�(ֻ��IF2Core�������������������)
     *@param IRCfgObj * lpConfig ������Ϣ
	 *@return I_OK �ɹ���I_NONE ʧ��.
     */
	virtual  int  FUNCTION_CALL_MODE SetConfig(const char * sPath,IRCfgObj * lpConfig)=0;

	///��������������������ӿ�
    /**
     *@param HS_SID iid �������Ĳ��ID
	 *@param HS_SID iid �������Ĳ���ӿ�
	 *@return I_OK �ɹ���I_NONE ʧ��.
     */
	virtual  int  FUNCTION_CALL_MODE SetDependService(HS_SID iid,IKnown * lpService)=0;

};


struct IF2UnPacker;//������ӿڣ�һ�����ڴ����������
struct IF2Packer;//������ӿڣ�һ�����ڷ���Ӧ������

///������һ������ʱ�Ļص��������ͣ��ڲ����ͬ����ʽ����ϵͳ�¼�����г�ʼ��ʱ�������߻ᴫ��һ���ص��������Ա���ͨ�����øú�����ͬ����������н��������֪ͨ������
/**�ûص������ĵ������ڵ���ʱ��������һ������ĳ�ʱʱ��(����)<p>
 *��ط����������PFinitxxxx()��ʼ������,IManager.ProcSysEvent()ϵͳ�¼�������<p> 
 *          ���������IF2Core.Load()����������ʼ��������IF2Core.ProcSysEvent()ϵͳ�¼�������<p>
 *@param int iMS  ���ƵĴ���ʱʱ��(����)
 */
typedef void (FUNCTION_CALL_MODE * PFOnSetTimeOut)( int iMS );

///��Ϣ������������Ҫ����
#define RET_PM_OK        0
///��Ϣ������������Ҫ����
#define RET_PM_NONE   	 1
///��Ϣ����������ϵͳ�����(����ARЭ��ӿڣ����붨��Ϊ-1)
#define RET_PM_ERR       -1

///ͳһ����ӿڣ�ʵ�ֱ��ӿڵĲ�����Ϳ��Ա��������ͳһ�������߹���
/**
 *����Ҫ�Բ���������߹���ͨ�����ʵ�ֵ�IKnown�ӿڵ�QueryInterface(SID_MANAGER,&lpMgr)�����Ի�ñ��ӿڣ�<p>
 *һ����������ά�����в���ṩ��IManager�ӿڣ�������Щ������ݹ���������ϵͳ�¼�����������ṩ�˽ӿڣ����޷��������߹���
 */
struct IManager : IKnown
{

	///�����������
    /**
	 *@param IUnPacker * lpInput  ���������������ӿڣ�Լ��function_id�ֶα�����ͬ�Ĺ����ܣ�ȡֵ��ʵ��������ȷ����һ���1��ʼ��ţ�function_id=0 Ĭ�ϱ�ʾȡ֧�ֵĹ����ܺ��б�
     *@param IPacker * lpOutput   ���Ӧ���������ӿ�[�������]
	 *@return RET_PM_OK �ɹ���RET_PM_NONE �����ݣ�RET_PM_ERR ϵͳ����(����Ĺ����ܺŲ�����)��������������ʾҵ���Դ���
     */
	virtual  int  FUNCTION_CALL_MODE ProcMngRequest(IF2UnPacker * lpInput,IF2Packer * lpOutput)=0;

	///�������Ӧ��
    /**������Ķ������������AS���͹������������յ�Ӧ��ʱ�ύ�˺�������
	 *@param IUnPacker * lpInput  ����Ӧ���������ӿ�
	 *@return I_OK �ɹ���I_NONE ʧ��.
	 */
	virtual  int  FUNCTION_CALL_MODE ProcMngAnswer(IF2UnPacker * lpInput)=0;

	///����ϵͳ�¼�
    /**����ܽ�һЩϵͳ�¼�ͳһ֪ͨ�������������
     *@param unsigned long dwMessageID       ϵͳ�¼����(�μ�MSG_XXXX����)
	 *@param unsigned long dwWParam          ��Ϣ����1(�ɲ�ͬ��dwMessageID�����嶨��)
     *@param unsigned long dwLParam          ��Ϣ����2(�ɲ�ͬ��dwMessageID�����嶨��)
     *@param PFOnSetTimeOut pfOnSetTimeOut   ���ó�ʱ�Ļص�����,ȱʡΪNULL,����֪ͨ�����߱�������ƻ���Ҫ����ʱ�������ɶԸ��¼��Ĵ������ָ��ʱ����ٴλص��ú���
	 *@return I_OK �ɹ���I_NONE ʧ��.
     */
	virtual  int  FUNCTION_CALL_MODE ProcSysEvent(unsigned long dwMessageID,unsigned long dwWParam,unsigned long dwLParam,
		                                          PFOnSetTimeOut pfOnSetTimeOut = NULL ) = 0;

};

///ϵͳ��ʼ������Ϣ(��ʱ���в�����ز��ѳ�ʼ�����)
#define MSG_START         1
///ϵͳֹͣ������Ϣ��ֹͣ�������������
#define MSG_STOP          2   
///ϵͳ�˳���Ϣ
#define MSG_EXIT          3 
///ϵͳ����ʼFork�ӽ��̵�֪ͨ��Ϣ(��ʱ���ؼ���Ϊ0�Ĳ���Ѽ��ز���ʼ�����)
#define MSG_FORK          4

struct tagBaseServiceInfo;

///ÿ�ֲ����Ҫ������ԭ���ṩ(����)�����������������Զ������Ա����������ض������������ʱ������ֱ��ʹ�ö�̬����������;
//@{
///���ز��ʵ���Ľӿ�ָ�룬���ڹ���ģʽ�Ĳ��ÿ�ε���getxxxxInstance()������ͬ��ʵ��ָ�룬����֧�ֶ�ʵ���Ĳ��ÿ�ε���getxxxxInstance()���ز�ͬ��ʵ��ָ�룻
/**
 * �ڵ��øò����PFinitxxxx��PFgetxxxxDependService����ʱ�����صĽӿ�ָ�����Ϊ��������,�Է����ʵ������¶������������ʵ�֡�
 */
typedef IKnown * (FUNCTION_CALL_MODE * PFgetxxxxInstance)( );

///��������������������ӿ�ID�����������Ĳ���ӿڻ��ڳ�ʼ��ǰ(PFinitxxxx������ǰ)��ע��
/**
 *@param   void * lp    ���ʵ������getxxxxInstance()���ص�ʵ��ָ��
 *@return  char * lpIDs ������������������ӿ�ID�б���
 *         HS_SID���ַ������б����һ���Ϊ���ַ���,���磺 "xxxxx\0yyyyy\0\0"����ʾ����xxxxx,yyyyy��������ӿڡ�
 */
typedef char * (FUNCTION_CALL_MODE * PFgetxxxxDependService)( void * );

///��ʼ������ָ�루�������в������̬���غ�ŵ��ã������ݳ�ʼ������˳����ã�
/**
 *@param   void * lp                     ���ʵ������getxxxxInstance()���ص�ʵ��ָ��
 *@param PFOnSetTimeOut pfOnSetTimeOut   ���ó�ʱ�Ļص�����,ȱʡΪNULL,����֪ͨ�����߱�������ƻ���Ҫ����ʱ�������ɶԵ�ǰ��������ָ��ʱ����ٴλص��ú���
 *@return  int                           I_OK �ɹ���I_NONE ʧ��.
 */
typedef int (FUNCTION_CALL_MODE * PFinitxxxx)( void * , PFOnSetTimeOut );
//@}


///һ���������Է�װ����������������һ�������Ϣ��ѯ�ӿڣ��Ա�����ʹ������ӿڶ�̬���ز��
//@{

///�������Ϣ��ѯ�������ߴ�iIndex=0��ʼ�����ѯ��ֱ������I_NONEΪֹ;
typedef int (FUNCTION_CALL_MODE * PFgetxxxxInfo)(int iIndex, tagBaseServiceInfo * ppv );

///�����Ϣ(��̬����ʱʹ��)
struct tagBaseServiceInfo
{
	///ͳһ��������Ĳ��ID(���ʵ�����ó�������ʾ)
	HS_SID ServiceID;
	///��������Ϣyyyymmdd
	int iVersion;
	///�����ʼ������ָ�룬�������ͨ���˺�����ʼ�����
    PFinitxxxx  Init;
	///��ȡ���ʵ������ָ�룬�������ͨ���˺�����ò��ʵ��
    PFgetxxxxInstance  getInstance;
	///���������ʼ��ʱ���������������ID(��������������ȳ�ʼ����)������������ݴ˺����ķ������ݣ��ڲ����ʼ��ǰΪ���ע��������������������ӿ�
	PFgetxxxxDependService getDependServices;
	///�������������Ϣ��һ��Ϊ��������
	const char * Caption;
};

//@}

#endif



#endif
