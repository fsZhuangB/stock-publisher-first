/** @file
* ����Demo.���ܲ���
* @author  �Ŵ���
* @author  �������ӹɷ����޹�˾
* @version 1.0
* @date    20160815
*/

#include "sdk_util.h"
#include "sdk_callback.h"

MyCapabilityTest * g_pMyCapabilityTest = NULL; //���ܲ��� 

/*
	���ܲ���.K��
*/
void HqSdkUtil::capability_k_line(list<MyProdCode> *pListCodes)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	my_log("\n\tֻ��ӡ600570������������Ϣ,10��֮һ,��ʾ'.'��\n");

	int iCandleNum = 6; //K����
	bool bSync = false; //�첽����

	if(! g_pMyCapabilityTest)
	{
		delete g_pMyCapabilityTest;
	}
	g_pMyCapabilityTest = new MyCapabilityTest(pListCodes->size(), pListCodes->size());//׼�����ܲ���.K�ߣ�һ��һ������ȡK��

	//ѭ�����
	list<MyProdCode>::iterator it;
	for(it = pListCodes->begin(); it != pListCodes->end(); it++)
	{
		const MyProdCode& myCode = *it;
		test_k_line(myCode.prod_code.c_str(), myCode.market.c_str(), iCandleNum, bSync);
	}
}

/*
	���ܲ���.����
*/
void HqSdkUtil::capability_snapshot(list<MyProdCode> *pListCodes)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	my_log("\n\tֻ��ӡ600570������������Ϣ,10��֮һ,��ʾ'.'��\n");

	bool bSync = false; //�첽����
	int size = pListCodes->size(); //������
	int m_iNumPackage = size; //һ��snapshot���װ��ȫ����������Ҳ�������� m_iNumPackage = 200.����һ������������ȥ200������. 
	int iNumCommand = (size + m_iNumPackage - 1) / m_iNumPackage; //������
	g_pMyCapabilityTest = new MyCapabilityTest(size, iNumCommand);//׼�����ܲ���.

	//ѭ�����
	for(int i=0; i<iNumCommand; i++)
	{
		int iBegin = i * m_iNumPackage;
		int iEnd = (i + 1) * m_iNumPackage - 1;
		iEnd = min(iEnd, size - 1);
		test_snapshot(pListCodes, iBegin, iEnd, bSync);//ȡ pListCode��[iBegin, iEnd] ��װ��һ��SnapShot�����С�
	}
}

/*
	���ܲ���constructor.
*/
MyCapabilityTest::MyCapabilityTest(int codes, int package)
	: m_iNumCodes(codes), m_iNumPackage(package)
{ 
	m_dwStartTime = getTickCount64(); 
	m_iNumPackageOK=0; 
	m_iNumPackageErr=0;
	m_eventCapabilityTest = NULL;
}

/*
	���ܲ���.���
*/
void MyCapabilityTest::Log()
{
	my_log("\n���Խ��:\n");
	list<MyCapabilityItem>::iterator it;
	int numOk = 0;	//��ȷ�걾

	int size = m_listGets.size();
	int ten_percent = (size / 10) > 0 ? (size / 10) : 1; //10��֮1
	for(it = m_listGets.begin(); it != m_listGets.end(); it ++)
	{
		const MyCapabilityItem& item = *it;
		numOk ++;

		if(numOk % ten_percent == 0) //ÿ1/10����ӡһ�¡�
		{//����my_log.ǿ�ƴ�ӡ
			printf(" (��%d֧,��ʱ%0.3f��) ", numOk, (float)(item.m_time-m_dwStartTime)/1000);
		}
		if(numOk == m_listGets.size()) //���һ��
		{//����my_log.ǿ�ƴ�ӡ
			printf("\n\t��ȷ%d֧ , ����%d֧ , ��ʱ%0.3f��\n", numOk, m_iNumCodes - numOk, (float)(item.m_time-m_dwStartTime)/1000);
		}
	} 
}