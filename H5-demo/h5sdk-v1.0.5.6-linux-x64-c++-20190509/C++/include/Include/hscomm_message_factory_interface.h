///������Ϣ�����ӿڶ���
/*******************************************************
  Դ��������:hscomm_message_factory_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ������Ϣ�����ӿڶ���
  ģ������:  ��Ϣ
  ����˵��:  ��Ϣ�����ӿڶ���
             
  ��    ��:  maoyinjie
  ��������:  20100801
  ��    ע:  ��windows��ע�⺯�����÷�ʽ��__stdcall

  �޸���Ա��maoyinjie 
  �޸����ڣ�20111220
  �޸�˵��������PushInForce�ӿ�
			�������ñ���������������ƵĽӿ�

20130319 yinghh ������Ϣ������ȡָ��ҵ��ŵ�ģ����Ϣ���������ݵĽӿ�
20130320 yinghh ������Ϣ������̬���ء����ġ�ģ����Ϣ�Ľӿ�
20130514 yinghh ������Ϣ������̬���ء����ġ�ģ����Ϣ�Ľӿ�
20130516 yinghh �����ͷŹ����Ľӿ�
20140429 yinghh ��������ģ��Ľӿ�ȡ��ҵ��Ų������޸ĺ���߼�Ϊ�������е�ģ��
*********************************************************/

#ifndef __HSCOMM_MESSAGE_FACTORY_INTERFACE_H__
#define __HSCOMM_MESSAGE_FACTORY_INTERFACE_H__

#include <Include/pluginid.h>
#include <Include/plugin_interface.h>
#include <Include/hscomm_message_interface.h>

///	�����Ϣ��Q�ӿ�,ȷ���̰߳�ȫ
struct IHsComQ : IKnown
{
	///	����Ϣ�����л��һ����Ϣ
	virtual IHsCommMessage* FUNCTION_CALL_MODE Pop(int iWaitTime, void** lppOwner, int iID=0)=0;
	///	����Ϣ�����в���һ���µ���Ϣ, ����0�ɹ�,��0:ʧ��,��Ҫ�������Լ��ͷŸ���Ϣ
	virtual int FUNCTION_CALL_MODE Push(IHsCommMessage* lpMsg, void* lpOwner, int iID=0)=0;
	/// ���Q����Ϣ����
	virtual int FUNCTION_CALL_MODE GetMSGsInQ()=0;
	///	��ʼ����Q�����������ڵ���Ϣ������0������
	virtual int FUNCTION_CALL_MODE Init(int iMaxMsgsInQ=0)=0;
	///	���Q�ڲ��������ڵ�������Ϣ����
	virtual int FUNCTION_CALL_MODE GetMaxMSGsInQ()=0;
	///	���QΪ��ʱ������Ĵ���
	virtual int FUNCTION_CALL_MODE GetIdles()=0;
	///	���Q���Ѵ�����Ϣ����
	virtual int FUNCTION_CALL_MODE GetDealMsgs()=0;
	///	����Q�������ѹ��������Ϣ����,ȱʡ0,������
	virtual int FUNCTION_CALL_MODE SetMaxMsgsInQ(int iMax)=0;

	//	maoyinjie 20111220 ǿ������,���ܶ�������ѹ��������
	///	����Ϣ�����в���һ���µ���Ϣ, ���ǳɹ�
	virtual int FUNCTION_CALL_MODE PushInForce(IHsCommMessage* lpMsg, void* lpOwner, int iID=0)=0;
	///	�������ñ���������������ƵĽӿ�
	virtual int FUNCTION_CALL_MODE SetOwnerID(HS_SID id)=0;
};

// ��ʾģ��İ汾��Ϣ
struct TemplateVersion
{
    int bizId;
    const char *version;
};

// ��Ϣ���湤��,Ӧ����Ҫ�õ���Ϣ�Լ�QʱӦ���򹤳�����,�̰߳�ȫ
// ��������ģ��Ľӿ�ȡ��ҵ��Ų������޸ĺ���߼�Ϊ�������е�ģ��
struct IHsComMessageFactory  : IKnown
{
	// ����Q����
	virtual IHsComQ* FUNCTION_CALL_MODE CreateESBQ()=0;
	// �ͷ�Q����
	virtual void FUNCTION_CALL_MODE DestroyESBQ(IHsComQ* lpESBQ)=0;

	// ������Ϣ
	virtual IHsCommMessage* FUNCTION_CALL_MODE GetESBMsg()=0;


	virtual IHsCommMessage* FUNCTION_CALL_MODE OpenBuffer(char *lpBuffer, int iLen)=0;
	//	ǿ�ƻ��һ��esbmsg,����esbmsg����������
	virtual IHsCommMessage* FUNCTION_CALL_MODE GetESBMsgByForce()=0;

	virtual void FUNCTION_CALL_MODE SetDefaultBizID(uint8 byDefaultBiz)=0;


	//	//	maoyinjie 20101223
//////////////////////////////////////////////////////////////////////////
	/// ����fieldid���fieldname
	/**
	 *@param int iFieldID		�ֶ�id
	 *@param int iBizModulID	����ʱ�õ���ҵ��ģ��
	 * @return fieldname, ���ʧ��,����""
	*/
	virtual const char* FUNCTION_CALL_MODE GetFieldNameByID(int iFieldID, int iBizModulID)=0;
	/// �������ֻ��id
	/**
	 *@param const char* lpFieldName		�ֶ���
	 *@param int iBizModulID	����ʱ�õ���ҵ��ģ��
	 * @return >=0�ֶ�ID	<0,˵��û�ҵ�
	*/
	virtual int FUNCTION_CALL_MODE GetFieldIDByName(const char* lpFieldName, int iBizModulID)=0;
	virtual const char* FUNCTION_CALL_MODE GetFuncNameByID(int iFuncD, int iPacketType, int iBizModulID)=0;

	//	���һ���ֶε�ȡֵ����
	virtual int FUNCTION_CALL_MODE GetFieldType(int iBizModulID, int iTagID)=0;
	//	���ĳ��array���͵��ֶ��ڲ�,�����ض���Ա��ȡֵ����
	virtual int FUNCTION_CALL_MODE GetElementType(int iBizModulID, int iTagID, int iIndex)=0;

	virtual const char * FUNCTION_CALL_MODE GetFuncNote(int iFuncD, int iPacketType, int iBizModulID) = 0;

    // 20130319 yinghh ���ӻ�ȡָ��ҵ��ŵ�ģ����Ϣ���������ݵĽӿ�
    /// ��ȡָ��ҵ��ŵ�ģ����Ϣ�Ķ��������ݣ����ӿڹ���Ϊ�������Ϣ���ʱʹ�ã�
	/**
	*@param businessId ҵ���
	*@param template_buffer ��ȡ��ģ����Ϣ�������ڴ��ַ[OUT]
    *@param template_buffer_length ��ȡ��ģ����Ϣ�����Ƴ���[OUT]
	*@return ����0��ʾ�ɹ�������-1��ʾ�����ڸ�ҵ��Ŷ�Ӧ��ģ����Ϣ
	*/
    virtual int FUNCTION_CALL_MODE GetTemplateByBusinessId(int businessId, const char **template_buffer, int *template_buffer_length) = 0;

    // 20130320 yinghh ������Ϣ������̬���ء����ġ�ģ����Ϣ�Ľӿڣ��˽ӿ�ֻ��h5sdkʹ�ã�
    virtual int FUNCTION_CALL_MODE LoadTemplate(IHSKnown *lpCfg, const char *template_buffer, int template_buffer_length) = 0;
    // 20130514 yinghh ������Ϣ������̬���ء����ġ�ģ����Ϣ�Ľӿڣ��˽ӿ�ֻ��h5sdkʹ�ã�
    virtual int FUNCTION_CALL_MODE LoadPlaintextTemplate(IHSKnown *lpCfg, const char *template_buffer, int template_buffer_length) = 0;

    // 20130516 yinghh �����ͷŹ����Ľӿ�
    virtual int FUNCTION_CALL_MODE Delete() = 0;

    // ��ȡ����ģ��İ汾��Ϣ
    // countΪ[IN|OUT]����
    virtual int FUNCTION_CALL_MODE GetTemplateVersion(TemplateVersion *templateVersion, size_t *count) = 0;

    /// ���ݹ�����������ȡ��Ӧ�Ĺ��ܺš������͡�ҵ���
    /**
	*@param funcName ��������
	*@param iFuncD ���ܺ�[OUT]
    *@param iPacketType ������[OUT]
    *@param iBizModulID ҵ���[OUT]
	*@return ����0��ʾ�ɹ�������-1��ʾ�����ڸù������ƶ�Ӧ��ģ����Ϣ
	*/
    virtual int FUNCTION_CALL_MODE GetIDByFuncName(const char *funcName, int *iFuncD, int *iPacketType, int *iBizModulID) = 0;

    // ��ȡָ��ҵ��š����ܺš������͵���Ϣģ������ֵ
    virtual int64 FUNCTION_CALL_MODE GetTemplateFeature(int businessId, int functionId, int packetType) = 0;
};



//��Ϣ���湤����������---------------------------
#ifdef __cplusplus
extern "C" { 
#endif
IKnown*	FUNCTION_CALL_MODE GetHsCommMessageFactoryInstance();
int		FUNCTION_CALL_MODE GetHsCommMessageFactoryInit(void* lpInstance, PFOnSetTimeOut pfOnSetTimeOut = NULL);
char*	FUNCTION_CALL_MODE GetHsCommMessageFactoryDependSvr(void * lpInstance);
int		FUNCTION_CALL_MODE GetHsCommMessageFactoryInfo(int iIndex, tagBaseServiceInfo* ppv);
IHsComMessageFactory * FUNCTION_CALL_MODE NewHsCommMessageFactory();

#ifdef __cplusplus
}
#endif


#endif
