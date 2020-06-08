/** @file
* 行情Demo.性能测试
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/

#include "sdk_util.h"
#include "sdk_callback.h"

MyCapabilityTest * g_pMyCapabilityTest = NULL; //性能测试 

/*
	性能测试.K线
*/
void HqSdkUtil::capability_k_line(list<MyProdCode> *pListCodes)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	my_log("\n\t只打印600570，其它代码信息,10分之一,显示'.'。\n");

	int iCandleNum = 6; //K线数
	bool bSync = false; //异步调用

	if(! g_pMyCapabilityTest)
	{
		delete g_pMyCapabilityTest;
	}
	g_pMyCapabilityTest = new MyCapabilityTest(pListCodes->size(), pListCodes->size());//准备性能测试.K线，一次一个代码取K线

	//循环命令。
	list<MyProdCode>::iterator it;
	for(it = pListCodes->begin(); it != pListCodes->end(); it++)
	{
		const MyProdCode& myCode = *it;
		test_k_line(myCode.prod_code.c_str(), myCode.market.c_str(), iCandleNum, bSync);
	}
}

/*
	性能测试.快照
*/
void HqSdkUtil::capability_snapshot(list<MyProdCode> *pListCodes)
{
	if(pListCodes == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	my_log("\n\t只打印600570，其它代码信息,10分之一,显示'.'。\n");

	bool bSync = false; //异步调用
	int size = pListCodes->size(); //代码数
	int m_iNumPackage = size; //一个snapshot包里，装入全部代码数。也可以试试 m_iNumPackage = 200.即，一个命令里塞进去200个代码. 
	int iNumCommand = (size + m_iNumPackage - 1) / m_iNumPackage; //命令数
	g_pMyCapabilityTest = new MyCapabilityTest(size, iNumCommand);//准备性能测试.

	//循环命令。
	for(int i=0; i<iNumCommand; i++)
	{
		int iBegin = i * m_iNumPackage;
		int iEnd = (i + 1) * m_iNumPackage - 1;
		iEnd = min(iEnd, size - 1);
		test_snapshot(pListCodes, iBegin, iEnd, bSync);//取 pListCode，[iBegin, iEnd] ，装入一个SnapShot命令中。
	}
}

/*
	性能测试constructor.
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
	性能测试.输出
*/
void MyCapabilityTest::Log()
{
	my_log("\n测试结果:\n");
	list<MyCapabilityItem>::iterator it;
	int numOk = 0;	//正确标本

	int size = m_listGets.size();
	int ten_percent = (size / 10) > 0 ? (size / 10) : 1; //10分之1
	for(it = m_listGets.begin(); it != m_listGets.end(); it ++)
	{
		const MyCapabilityItem& item = *it;
		numOk ++;

		if(numOk % ten_percent == 0) //每1/10，打印一下。
		{//不用my_log.强制打印
			printf(" (第%d支,耗时%0.3f秒) ", numOk, (float)(item.m_time-m_dwStartTime)/1000);
		}
		if(numOk == m_listGets.size()) //最后一个
		{//不用my_log.强制打印
			printf("\n\t正确%d支 , 错误%d支 , 耗时%0.3f秒\n", numOk, m_iNumCodes - numOk, (float)(item.m_time-m_dwStartTime)/1000);
		}
	} 
}