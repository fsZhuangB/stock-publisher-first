///	������Ϣ�ӿڶ���
/*******************************************************
  Դ��������:hscomm_message_interface.h
  �������Ȩ:�������ӹɷ����޹�˾
  ϵͳ����:  ������Ϣ�ӿڶ���
  ģ������:  ��Ϣģ��
  ����˵��:  ��Ϣ�ӿڶ���
             
  ��    ��:  maoyinjie
  ��������:  20100801
  ��    ע:  ��windows��ע�⺯�����÷�ʽ��__stdcall

yinghh    20130408 ���ظ������ӽӿڣ�ʹ�����һ�������N���ռ�¼������ҵ����ڼ�¼������֪��������Ż�����
yinghh    20130508 ������Ϣ���½ӿ�Clone��Duplicate
*********************************************************/

#ifndef HSCOMM_MESSAGE_INTERFACE_H
#define HSCOMM_MESSAGE_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>

//	�����ƽ̨�Ļ�����������
#ifdef _WIN32
	typedef char				int8;
	typedef short				int16;
	typedef int					int32;
	typedef __int64				int64;
	typedef unsigned char		uint8;
	typedef unsigned short		uint16;
	typedef unsigned int		uint32;
	typedef unsigned __int64	uint64;
#else
	#include <sys/types.h>
	#if defined(__linux__)
		#include <stdint.h>
	#endif
	typedef int8_t				int8;
	typedef int16_t				int16;
	typedef int32_t				int32;
	typedef int64_t				int64;
	typedef uint8_t				uint8;
	typedef uint16_t			uint16;
	typedef uint32_t			uint32;
	typedef uint64_t			uint64;
#endif


#ifdef _WIN32
	#if !defined( FUNCTION_CALL_MODE )
		#define FUNCTION_CALL_MODE		__stdcall
	#endif
#else
	#define FUNCTION_CALL_MODE
#endif




//	�������Ͷ���
const uint8 TypeInt8=0;
const uint8 TypeuInt8=1;
const uint8 TypeInt16=2;
const uint8 TypeuInt16=3;
const uint8 TypeInt32=4;
const uint8 TypeuInt32=5;
const uint8 TypeInt64=6;
const uint8 TypeuInt64=7;
const uint8 TypeDouble=8;
const uint8 TypeString=9;
const uint8 TypeVector=10;
const uint8 TypeRaw=11;
const uint8 TypeIPV4=12;
const uint8 TypeIPV6=13;
const uint8 TypeMac=14;
const uint8 TypeArray=15;
const uint8 TypeSequence=16;
const uint8 TypeUnKnown=255;



#ifndef IHS_KNOWN
#define IHS_KNOWN

///	����ӿ�ͳһ�Ĳ�ѯ�����ýӿڣ����в���ṩ�Ľӿڶ�Ҫʵ�� IKnown (����COM��׼)
struct IHSKnown
{
	///�ӿڲ�ѯ
	/**��ѯ�뵱ǰ�ӿ���ص������ӿڣ�������Բ鵽 IIoC, IManager ��
	 *@param HS_SID  iid  �ӿ�ȫ��Ψһ��ʶ
	 *@param IKnown **ppv ����iid��Ӧ�Ľӿ�ָ��
	 *@return I_OK �ɹ���I_NONE δ�鵽iid ��Ӧ�ӿ�
	 */
	virtual unsigned long  FUNCTION_CALL_MODE QueryInterface( const char * iid, IHSKnown **ppv ) = 0;
	///���ýӿڣ����ü�����һ(���߳�����ʱ������ʵ�ִ�����Ҫ�Լ���ֵ�������޸�)
	virtual unsigned long  FUNCTION_CALL_MODE AddRef() = 0;
	///�ͷŽӿڣ����ü�����һ������Ϊ0ʱ�ͷŽӿڵ�ʵ�ֶ���(���߳�����ʱ������ʵ�ִ�����Ҫ�Լ���ֵ�����������޸�)
	virtual unsigned long  FUNCTION_CALL_MODE Release() =  0;
};
#endif

///	TAG��ֵ��,֧��������ʽ
struct IHsCommTagItem : IHSKnown
{
	/////////////////////////////////////	��ȡֵ	////////////////////////////////////////
	///��õ��ֽ�������ʽ��ֵ	
	/**
	*@param int	iIndex:	��Ҫ��������ڵڼ���Ԫ�ص�ֵ
	*@return	��ֵ
	**/
	virtual uint8	FUNCTION_CALL_MODE GetInt8(uint32 dwIndex=0) const=0;				//	0
	///���˫�ֽ�������ʽ��ֵ
	/**
	*@param int	iIndex:	��Ҫ��������ڵڼ���Ԫ�ص�ֵ
	*@return	��ֵ
	**/
	virtual uint16	FUNCTION_CALL_MODE GetInt16(uint32 dwIndex=0) const=0;				//	0
	///���4�ֽ�������ʽ��ֵ
	/**
	*@param int	iIndex:	��Ҫ��������ڵڼ���Ԫ�ص�ֵ
	*@return	��ֵ
	**/
	virtual uint32	FUNCTION_CALL_MODE GetInt32(uint32 dwIndex=0) const=0;				//	0
	///���64λ������ʽ��ֵ
	/**
	*@param int	iIndex:	��Ҫ��������ڵڼ���Ԫ�ص�ֵ
	*@return	��ֵ
	**/
	virtual uint64	FUNCTION_CALL_MODE GetInt64(uint32 dwIndex=0) const=0;				//	0
	///��ø�����ʽ��ֵ
	/**
	*@param int	iIndex:	��Ҫ��������ڵڼ���Ԫ�ص�ֵ
	*@return	��ֵ
	*Double		�������紫��ʱ,�ڲ����Ὣdoubleת����int64����int32(����ģ���ж����С����λ��)
				����,����double����һ�����ٶ���,��һ����,���ɱ�����ܻ�������ʧ��,����
				�ýӿھ�����Ҫ��
	**/
	virtual double	FUNCTION_CALL_MODE GetDouble(uint32 dwIndex=0) const=0;				//	0.0
	///���rawdata�ĳ���
	/**
	*@param int iIndex:			��ȡ�����ڵڼ���Ԫ��
	*@return	����
	**/
	virtual int		FUNCTION_CALL_MODE 	GetRawDataLen(uint32 dwIndex=0) const=0;		//	0
	///���rawdata��ֵ
	/**
	*@param int* ilpRawDataLen:	����rawdata�ĳ���
	*@param int iIndex:			��ȡ�����ڵڼ���
	*@return	ָ����ֵ��ָ��
	**/
	virtual const void* FUNCTION_CALL_MODE GetRawData(int* ilpRawDataLen=NULL, uint32 dwIndex=0) const=0;		// "" 0
	///����ִ���ʽ��ֵ:
	/**
	*@param int	iIndex:	��Ҫ��������ڵڼ���Ԫ�ص�ֵ
	*@return	ָ����ֵ��ָ��
	**/
	virtual const char* FUNCTION_CALL_MODE GetString(uint32 dwIndex=0) const=0;			//	""
	

	/// ��������ڳ�Ա���� 
	virtual int FUNCTION_CALL_MODE GetCount() const =0;
	/// �Ƿ���ڵ�iIndex����Ա
	virtual bool FUNCTION_CALL_MODE IsExist(uint32 dwIndex=0) const =0;
	//	��õ�ǰ�������������
	virtual int  FUNCTION_CALL_MODE GetValueType(uint32 dwIndex=0) const=0;	


	///	����ֵ
	/**
	* ����������ʽ��ֵ
	*@param int	iIndex:	��Ҫ���������ڵڼ���Ԫ�ص�ֵ
	*@param char cValue:	��ֵ
	*@return	��
	**/
	virtual void FUNCTION_CALL_MODE SetInt8(uint8 byValue, int iIndex=0)=0;
	/**
	* ����������ʽ��ֵ
	*@param int	iIndex:	��Ҫ���������ڵڼ���Ԫ�ص�ֵ
	*@param uint16 wValue:	��ֵ
	*@return	��
	**/
	virtual void FUNCTION_CALL_MODE SetInt16(uint16 wValue, int iIndex=0)=0;
	/**
	* ����������ʽ��ֵ
	*@param int	iIndex:	��Ҫ���������ڵڼ���Ԫ�ص�ֵ
	*@param int iValue:	��ֵ
	*@return	��
	**/
	virtual void FUNCTION_CALL_MODE SetInt32(uint32 dwValue, int iIndex=0)=0;
	/**
	* ����64λ������ʽ��ֵ
	*@param int	iIndex:	��Ҫ���������ڵڼ���Ԫ�ص�ֵ
	*@param int64 i64Value:	��ֵ
	*@return	��
	**/
	virtual void FUNCTION_CALL_MODE SetInt64(uint64 i64Value, int iIndex=0)=0;
	/**
	* ���ø�����ʽ��ֵ
	*@param int	iIndex:	��Ҫ���������ڵڼ���Ԫ�ص�ֵ
	*@param double dfValue:	��ֵ
	*@return	��
	*Double�ӿھ�����Ҫ��
	**/
	virtual void FUNCTION_CALL_MODE SetDouble(double dfValue, int iIndex=0)=0;	
	/**
	* �����ִ���ʽ��ֵ
	*@param int	iIndex:	��Ҫ���������ڵڼ���Ԫ�ص�ֵ
	*@param const char* lpValue:	��ֵ
	*@return	��
	**/
	virtual void FUNCTION_CALL_MODE SetString(const char* lpValue, int iIndex=0)=0;
	/**
	* ����rawdata��ʽ��ֵ
	*@param int	iIndex:	��Ҫ���������ڵڼ���Ԫ�ص�ֵ
	*@param const void* lpRawData:	��ֵ
	*@param int iRawDataLen:	��ֵ����
	*@return	��
	**/
	virtual void FUNCTION_CALL_MODE SetRawData(const void* lpRawData, int iRawDataLen, int iIndex=0)=0;

	////////////////////////	������������Ч��Ա,������������������GetXXX�����ӿڷ��ʳ�Ա,����iIndexֵ����-1	//////////////////
	//	��ֹ20100816	��δʵ��
	/// ת����һ����Ч��Ա
	/**
	*@return	0:�޳�Ա 	����:���г�Ա
	**/
	virtual int FUNCTION_CALL_MODE First()=0;
	/// ������һ����Ч��Ա
	/**
	*@return	0:�޳�Ա 	����:���г�Ա
	**/
	virtual int FUNCTION_CALL_MODE Next()=0;


	virtual bool FUNCTION_CALL_MODE IsDouble()=0;



	//	2011/04/19	����	���½ӿ���ʱδʵ��
	virtual void SetIPV4(const char* lpIPV4)=0;	//	����	192.168.1.1	�ĵ�ַ
	virtual void SetIPV6(const char* lpIPV6)=0;	//	����	fe80::226:55ff:fe1f:18cc	�ĵ�ַ
	virtual void SetMac(const char* lpMac)=0;		//	����	00-1C-23-2A-A6-3A	�ĵ�ַ
	virtual char* GetIPV4()=0;
	virtual char* GetIPV6()=0;
	virtual char* GetMac()=0;

    // ��ȡ��ģ���ﶨ���С��λ��
    virtual int FUNCTION_CALL_MODE GetShift() = 0;
};


///	ҵ����Ϣ,�����Ƕ��¼��һ�������,Ҳ�����ǵ���¼,ȡ���ھ�����Ϣ��ģ��
struct  IBizResultSet : public IHSKnown		//	�䱾����group
{
	/**
	*	���ĳ����ֵ�Ķ���ָ��
	*@param int	iFieldTag:��Ҫ�����ֵ��TAG
	*@return	ָ����ֵ�����ָ��(�����Ϣ�ڲ����ڸ�TAG,��᷵��һ��ȱʡ�Ķ���,ȷ�����طǿ�)
	**/
	virtual IHsCommTagItem*	FUNCTION_CALL_MODE GetItem(int iFieldTag) const =0;

	///�ж��Ƿ�Ϊ��
    /**@return 1 �ǣ�0 ����;
      */
    virtual int FUNCTION_CALL_MODE IsEmpty()const =0;	
    ///�ж��Ƿ�Ϊ��β
    /**@return 1 �ǣ�0 ����;
      */
    virtual int FUNCTION_CALL_MODE IsEOF() const =0;
    ///ȡ��һ����¼
    /**@return 1 ���ڼ�¼��0 �Ѿ��������
      */
    virtual int FUNCTION_CALL_MODE Next() =0;
	/**
	*@param int	iFieldTag:����Ƿ����iFieldTag
	*@return	0:������	��0����
	**/
	virtual int	FUNCTION_CALL_MODE IsExist(int iFieldTag) const  = 0;

	//	�������
	/**
	*@return	��������
	**/
	virtual int	FUNCTION_CALL_MODE GetLines() const = 0;

	/// �������Record�е���ͨ�ֶ�
	/**
	*@param wTagID�����������ط�NULLʱ����ӦItem��TAGֵ[OUT]
	*@return NULL��ʾ��������������Ϊ������õ�Item
	*/
	virtual IHsCommTagItem* FUNCTION_CALL_MODE GetPureTag(uint16 &wTagID) const = 0;

    /// �ڿ�ʼ������¼�е���ͨ�ֶ�ʱ��Ҫ�ȵ���һ�α�����
	/**
	*/
	virtual void FUNCTION_CALL_MODE BeginTour() = 0;
};




//////////////////////////////////////////////////////////////////////////
///	��Ϣ�Ǹ��ݹ�Ķ���
struct  IGroup;
///	��Ϣ�е�ÿ����¼
struct IRecord : IHSKnown
{
	/**
	*	���ĳ����ֵ�Ķ���ָ��
	*@param int	iFieldTag:��Ҫ�����ֵ��TAG
	*@return	ָ����ֵ�����ָ��(�����Ϣ�ڲ����ڸ�TAG,�򴴽�����,�������ʧ��,�򷵻�һ��ȱʡ����,ȷ�����طǿ�)
	**/
	virtual IHsCommTagItem*	FUNCTION_CALL_MODE GetItem(int iFieldTag) const=0;

	/**
	*@param int	iFieldTag:����Ƿ����iFieldTag(��ͨ�ֶκ�sequence�����,����û���ȷ֪��
		�Լ���Ҫ��������ͨ�ֶλ���sequence,����IsExistPure��IsExistSequence���,����������)
	*@return	0:������	��0����
	**/
	virtual bool	FUNCTION_CALL_MODE IsExist(int iFieldTag) const  = 0;

	/// ����Ϣ��ɾ��һ����
	/**
	*@param int	iFieldTag:��Ҫɾ��TAG,��ɾ����ͨ��,���������sequence,�������RemoveGroup������
	*@return 0:�ɹ�		����:ʧ��
	**/
	virtual int	FUNCTION_CALL_MODE RemoveTag(int iFieldTag) = 0;
	/// ����¼������һ���ظ��飬����ظ����Ѵ棬�򷵻ص����Ѵ����ظ���ӿڡ�
	/**
	*@param int iGroupTag	�ظ���(������)Tag(��������Ϊһ���ظ����TAG����)
							����Ψһ�ı�־��GROUP
	*@return  IGroup �ṹָ��,����Դ����ʱ,�᷵��NULL

	��Ϊ��	����һ���յ�Group�ṹ�����ÿ�Group�ṹ���뵽��¼�У�ͬʱ����
			�����ɵĸ�Group�ṹָ�롣������Ա�����ڻ�ø�ָ��󣬽���ȥ
			��Group�ṹ���в�����������Group�в��������¼��
	*/
	virtual IGroup* FUNCTION_CALL_MODE SetGroup( int iGroupTag ) = 0;

	/// ȡָ�����ظ���
	/**
	 *@param int iGroupTag �ظ���Tag��FIXЭ����Ϊ������Tag
	 *@return IGroup �ṹָ��; ������ظ��鲻���ڣ�����NULL;
	 */
	virtual IGroup * FUNCTION_CALL_MODE GetGroup( int iGroupTag ) const = 0;

	/// ����Ϣ��ɾ��һ���ظ���
	virtual void FUNCTION_CALL_MODE RemoveGroup( int iGroupTag ) = 0;

	/// �������Record�е���ͨ�ֶ�
	/**
	*@param wTagID�����������ط�NULLʱ����ӦItem��TAGֵ[OUT]
	*@return NULL��ʾ��������������Ϊ������õ�Item
	*/
	virtual IHsCommTagItem* FUNCTION_CALL_MODE GetPureTag(uint16& wTagID) = 0;

	/**
	*@param int	iFieldTag:����Ƿ����iFieldTag(ֻ�����ͨ�ֶ�)
	*@return	0:������	��0����
	**/
	virtual bool FUNCTION_CALL_MODE IsExistPure(int iFieldTag) const  = 0;
	/**
	*@param int	iFieldTag:����Ƿ����iFieldTag(ֻsequence)
	*@return	0:������	��0����
	**/
	virtual bool FUNCTION_CALL_MODE IsExistSequence(int iGroupTag) const  = 0;

    /// �ڿ�ʼ������¼�е���ͨ�ֶ�ʱ��Ҫ�ȵ���һ�α�����
	/**
	*/
	virtual void FUNCTION_CALL_MODE BeginTour() = 0;

	//	�ж�ĳ��TAG�ǲ���double����
	virtual bool FUNCTION_CALL_MODE IsDouble(int iFieldTag) = 0;

    // ��record�����ݸ��Ƶ�����¼����
    // ע�⣡������Ҫȷ����2����¼��ģ����һ����
    // ������Ŀǰֻ�᷵��0
    virtual int FUNCTION_CALL_MODE CopyFrom(IRecord *record) = 0;

    // ��ȡĳ���ֶ���ģ���ﶨ���С��λ��
    virtual int FUNCTION_CALL_MODE GetShift(int iFieldTag) = 0;

    /// �ڿ�ʼ������¼�е��ֶ�ʱ��Ҫ�ȵ���һ�α�����
	/**
	*/
	virtual void FUNCTION_CALL_MODE BeginTourEx() = 0;

    /// �������Record�е��ֶ�
	/**
	*@param wTagID�����������ط�NULLʱ����ӦItem��Group��TAGֵ[OUT]
    *@param isGroup�����������ط�NULLʱ�Ƿ���Group[OUT]
	*@return NULL��ʾ��������������Ϊ������õ�Item��Group����Ҫǿ������ת��
	*/
	virtual void * FUNCTION_CALL_MODE GetTagEx(uint16& wTagID, bool &isGroup) = 0;

    /**
	*	���ĳ����ֵ�Ķ���ָ��
	*@param int	iFieldTag:��Ҫ�����ֵ��index
	*@return	ָ����ֵ�����ָ��(����������򷵻�NULL)
	**/
	virtual IHsCommTagItem * FUNCTION_CALL_MODE GetItemByIndex(int index) const = 0;

    /// ����Ϣ��ɾ��һ����
	/**
	*@param int	index:��Ҫɾ��TAG��index,��ɾ����ͨ��,���������sequence,�������RemoveGroup������
	*@return 0:�ɹ�		����:ʧ��
	**/
	virtual int	FUNCTION_CALL_MODE RemoveTagByIndex(int index) = 0;

    /// �������Record�е��ֶ�
	/**
	*@param wTagID�����������ط�NULLʱ����ӦItem��Group��TAGֵ[OUT]
    *@param isGroup�����������ط�NULLʱ�Ƿ���Group[OUT]
    *@param index�����������ط�NULLʱ����ӦItem��Group��indexֵ[OUT]
	*@return NULL��ʾ��������������Ϊ������õ�Item��Group����Ҫǿ������ת��
	*/
	virtual void * FUNCTION_CALL_MODE GetTagEx2(uint16 &wTagID, bool &isGroup, int &index) = 0;
};

///�ظ������ӿڣ���ʾ������¼��һ������(DataSet)
struct  IGroup :public IHSKnown
{
	/// �����ظ����ڼ�¼����
	virtual int FUNCTION_CALL_MODE GetRecordCount() const = 0;

	/// ȡ�ظ����е�ĳ����¼
	/**
	 *@param int num �ڼ�����¼(num��0��ʼ)
	 *@return IRecord �ṹָ��
	 */
	virtual IRecord * FUNCTION_CALL_MODE GetRecord(int num) const = 0;

	/// ���ظ�����׷��һ���հ׼�¼
	/**
	 * @return IRecord ׷�ӵļ�¼ָ��,�����Դ����,���ܻ᷵��NULL
	��Ϊ:	����һ��AddRecord����,��������һ���յ� IRecord,���ҽ��� IRecord ����
			�ظ���,���ظմ����� IRecord ָ��,������Ա��ø�ָ���,������ IRecord
			�в����ֶ�(��ͨ�ֶλ�������һ���ظ����ֶ�)

	*/
	virtual IRecord * FUNCTION_CALL_MODE AddRecord() = 0;

	/// һ���Բ���count���ռ�¼������������ͨ��GetRecord����ȡ��Ӧ�±�ļ�¼
	/**
	*@param int count ��Ҫ����ļ�¼��
	*@return int ����0��ʾ�ɹ���-1��ʾ�ڴ�����ʧ��
	*/
    virtual int FUNCTION_CALL_MODE AddRecords(int count) = 0;

    /**
	*	����Tag���index
	*@param int	iFieldTag:��Ҫ����±��TAG
	*@return	Tag��Ӧ��index������Ҳ���������255
	**/
	virtual int	FUNCTION_CALL_MODE GetIndexByFieldID(int iFieldTag) const = 0;
};

// ����������Ϣʱ,���� IRecord �� IGroup ��ʵ�ֵݹ�Ķ���,����,���ں�������ϵͳʹ�õĽӿڶ���,����IHsCommMessage��IBizResultSet���ɴ���
//	����Ϣ�Ĳ���,��������Ϊ����Ϣ�������Ϣ��Ĳ���,���,��ȷҪ������Ϣͷ,����ͨ��GetHead�õ�ͷ���ٲ���
struct IHsCommMessage: IHSKnown
{
	/**
	*	�������ĳ����ֵ�Ķ���ָ��
	*@param int	iFieldTag:��Ҫ�����ֵ��TAG
	*@return	ָ����ֵ�����ָ��(�����Ϣ�ڲ����ڸ�TAG,��᷵��һ��ȱʡ�Ķ���,ȷ�����طǿ�)
	**/
	virtual IHsCommTagItem * FUNCTION_CALL_MODE GetItem(int iFieldTag)=0;
	/**
	*	��ý�����Ķ���ָ��
	*@param int	iFieldTag:��Ҫ��ý������TAG
	*@return	ָ�����������ָ��
	*	ע��:���صĽ����������ȡֵ,����������ֵ
	**/
	virtual IBizResultSet * FUNCTION_CALL_MODE GetBizResultSet(int iFieldTag) = 0;

	/**
	*@param int	iFieldTag:����Ƿ����iFieldTag
	*@return	0:������	��0����
	**/
	virtual int			FUNCTION_CALL_MODE IsExist(int iFieldTag) const  = 0;

	///	���ݱ���������Ϣ�����ڵĸ�����
	/**
	* ���ݱ���������Ϣ�����ڵĸ�����
	*@param const void* lpMessageBuffer:	����
	*@param int iMsgLen:					���ĳ���
	*@return 0:�ɹ�		����:ʧ��
	**/
	virtual int			FUNCTION_CALL_MODE SetBuffer(const void* lpMessageBuffer, int iMsgLen) = 0;
	/**
	* ���������ڵĸ�����ֵ�������շ�װ�ɱ��ķ���,(����װЭ���ڲ�����ֵ)
	*@param int* ilpMsgLen:	��װ���ĵĳ���
	*@return ����,���ʧ��,����NULL
	**/
	virtual void*		FUNCTION_CALL_MODE GetBuffer(int* ilpMsgLen) = 0;

	/// ����Ϣ��ɾ��һ����
	/**
	*@param int	iFieldTag:��Ҫɾ��TAG
	*@return 0:�ɹ�		����:ʧ��
	**/
	virtual int			FUNCTION_CALL_MODE RemoveTag(int iFieldTag) = 0;
	/// ����¼������һ���ظ��飬����ظ����Ѵ棬�򷵻ص����Ѵ����ظ���ӿڡ�
	/**
	*@param int iGroupTag	�ظ���(������)Tag(��������Ϊһ���ظ����TAG����)
							����Ψһ�ı�־��GROUP
	*@return  IGroup �ṹָ��

	��Ϊ��	����һ���յ�Group�ṹ�����ÿ�Group�ṹ���뵽��¼�У�ͬʱ����
			�����ɵĸ�Group�ṹָ�롣������Ա�����ڻ�ø�ָ��󣬽���ȥ
			��Group�ṹ���в�����������Group�в��������¼��
	*/
	virtual IGroup* FUNCTION_CALL_MODE SetGroup( int iGroupTag ) = 0;

	/// ȡָ�����ظ���
	/**
	 *@param int iGroupTag �ظ���Tag��FIXЭ����Ϊ������Tag
	 *@return IGroup �ṹָ��; ������ظ��鲻���ڣ�����NULL;
	 */
	virtual IGroup * FUNCTION_CALL_MODE GetGroup( int iGroupTag ) const = 0;


	//	���½ӿڽ�������Ϣ��Ҫ,������Ϣ�ڲ���Record��Group����Ҫ
	//	��Ϣ�м���ʱ���
	virtual int	FUNCTION_CALL_MODE AddTimeStamp(char* lpText) = 0;
	//	���ºۼ�(ÿ��������Ĳ����Ҫ�����Լ��ĺۼ�)
	virtual int FUNCTION_CALL_MODE AddTrack(const char* lpID)=0;
	virtual int FUNCTION_CALL_MODE AddIntTrack(int iID)=0;
	
	//	���ͷ����Ϣ,
	virtual IRecord * FUNCTION_CALL_MODE GetHead()=0;
	//	���ҵ����
	virtual IRecord * FUNCTION_CALL_MODE GetBody()=0;


	//	���µĲ�����ֱ�Ӳ�����Ϣͷ�еļ�������TAG,�Լ򻯶���Ϣͷ�Ĳ���
	virtual int FUNCTION_CALL_MODE GetFunction() const=0;
	virtual int FUNCTION_CALL_MODE GetPacketType()const=0;
	virtual int FUNCTION_CALL_MODE GetBizID()const=0;
	virtual int FUNCTION_CALL_MODE SetFunction(uint32 dwFuncID)=0;
	virtual int FUNCTION_CALL_MODE SetPacketType(uint32 dwPacketType)=0;
	virtual int FUNCTION_CALL_MODE SetBizID(uint32 dwBizID)=0;


	///	�ڴ���ⱨʧ��ʱ,���Ի��Ϊʲôʧ�ܵ�ԭ��
	virtual const char* FUNCTION_CALL_MODE GetLastErrInfo()=0;
	/// �����Ϣ,׼��������֯һ���µ���Ϣ
	virtual void FUNCTION_CALL_MODE Clear()=0;

    /**
    *	����һ���ͱ���Ϣһģһ������Ϣ��ע�⣡�����Ƴ�������Ϣ�ĳ�ʼ���ü���Ϊ1��
    *   ������ɺ󣬱����Ƴ�������Ϣ��ԭ��Ϣ�������
    *@return	�����Ƴ�������Ϣ
    **/
    virtual IHsCommMessage * FUNCTION_CALL_MODE Clone() = 0;

    /**
    *	���Ʊ���Ϣ��һ��ֻ������
    *   ҵ��������������Ȿ�������߼������ӱ���Ϣ�����ü�����Ȼ�󷵻ر���Ϣ
    *   ҵ�����Ҫ��ϸ���𱾷�����Clone����������
    *   ��ҵ�����Ҫ�޸��������ʱ�����Ե��ø�����Clone��������ȡ����Ϣ��Ȼ����ܽ����޸�
    *@return    ֻ������
    **/
    virtual IHsCommMessage * FUNCTION_CALL_MODE Duplicate() = 0;

    /**
    *   �ѱ���Ϣ���Ƴ�hsMessage��һ������
    *   Ҫ����Ϣ��hsMessage��ͬһ�����͵���Ϣ
    **/
    virtual int FUNCTION_CALL_MODE CopyFrom(IHsCommMessage *hsMessage) = 0;

    /**
	* ���������ڵĸ�����ֵ�������շ�װ�ɱ��ķ���,(����װЭ���ڲ�����ֵ)
	*@param int* ilpMsgLen:	��װ���ĵĳ���
	*@return ����,���ʧ��,����NULL
	**/
	virtual void*		FUNCTION_CALL_MODE GetBufferEx(int* ilpMsgLen, char *buffer, int size) = 0;

    /**
    *   �ѱ���Ϣ���Ƴ�hsMessage��һ������
    *   ��ǿ��Ҫ����Ϣ��hsMessage��ͬһ�����͵���Ϣ
    **/
    virtual int FUNCTION_CALL_MODE CopyFromByTag(IHsCommMessage *hsMessage) = 0;
};

struct IHsComMessageFactory;

//	�����ΪAPI��,����Ҫ��ʼ��
#ifdef EXPORT_API
	
#ifdef __cplusplus
extern "C" { 
#endif
	/// ��ʼ����Ϣģ��
	/**
	 *@param const char* lpTemplateFile ��Ϣģ���ļ���
	 *@param int iBizModulID	��Ҫ��ʼ���ĸ�ҵ��(��Ϊ��һ��ģ���ļ��л���ڶ��ҵ��,һ���Ӧһ���ͻ���ֻ��Ҫ��עһ��ҵ�񼴿�)
	 * @return 0�ɹ�  ����ʧ��
	*/
	int				FUNCTION_CALL_MODE Init(IHSKnown* lpCfg, const char* lpTemplateFile, int iBizModulID);
	
    // ���ݹ��ܺ���������Ϣ,��Ϊ��ͬ�����в�ͬ����Ϣģ��
	IHsCommMessage* FUNCTION_CALL_MODE CreateMessage(int iFunc, int iPacketType);

    // �����µ���Ϣ����
    IHsComMessageFactory * FUNCTION_CALL_MODE CreateMessageFactory();

	/// ����fieldid���fieldname
	/**
	 *@param int iFieldID		�ֶ�id
	 *@param int iBizModulID	����ʱ�õ���ҵ��ģ��
	 * @return fieldname, ���ʧ��,����""
	*/
	const char* FUNCTION_CALL_MODE GetFieldNameByID(int iFieldID, int iBizModulID);
	/// �������ֻ��id
	/**
	 *@param const char* lpFieldName		�ֶ���
	 *@param int iBizModulID	����ʱ�õ���ҵ��ģ��
	 * @return >=0�ֶ�ID	<0,˵��û�ҵ�
	*/
	int FUNCTION_CALL_MODE GetFieldIDByName(const char* lpFieldName, int iBizModulID);
	const char* FUNCTION_CALL_MODE GetFuncNameByID(int iFuncD, int iPacketType, int iBizModulID);

	//	���һ���ֶε�ȡֵ����
	int FUNCTION_CALL_MODE GetFieldType(int iBizModulID, int iTagID);
	//	���ĳ��array���͵��ֶ��ڲ�,�����ض���Ա��ȡֵ����
	int FUNCTION_CALL_MODE GetElementType(int iBizModulID, int iTagID, int iIndex);

	//	maoyinjie 20101230
	const char* FUNCTION_CALL_MODE GetFuncNote(int iFuncD, int iPacketType, int iBizModulID);
#ifdef __cplusplus
}
#endif	//	__cplusplus
#endif	//	EXPORT_API
#endif	//	HSCOMM_MESSAGE_INTERFACE_H
