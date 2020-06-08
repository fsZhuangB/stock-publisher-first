/** @file
* 行情Demo.SDK使用例子
* @author  张春雷
* @author  恒生电子股份有限公司
* @version 1.0
* @date    20160815
*/
#include "my_vld.h"

#include "sdk_data_parser.h"
#include "sdk_util.h"
#include "main_message_queue.h"
#include "main_environment.h"

/*///////////////////////////////////////////////////////////////////////////////////////////////////
	sdk数据包
///////////////////////////////////////////////////////////////////////////////////////////////////*/
CSdkPackage::CSdkPackage(IHsCommMessage* package)
{
	m_hsMsgPackage = package;
	m_timeReceived = getTickCount64();
}
CSdkPackage::~CSdkPackage()
{
	if(m_hsMsgPackage)
	{
		//释放!!!
		m_hsMsgPackage->Release();
	}
}
void CSdkPackage::Handle(void)
{
	bool bPackageOK = true;
	//判断是否执行成功
	int headErrorNo = m_hsMsgPackage->GetHead()->GetItem(H5PROTO_TAG_ERROR_NO)->GetInt32();
	if(headErrorNo != 0)
	{//错误处理
		int len = m_hsMsgPackage->GetHead()->GetItem(H5PROTO_TAG_USER_KEY)->GetRawDataLen(0); //只取第一个用户自定义Key.
		char *user_key = (char *)m_hsMsgPackage->GetHead()->GetItem(H5PROTO_TAG_USER_KEY)->GetRawData(&len);//用户输入的key.用于与异步命令一一对应。
		my_log("\n\t%s: errNo=%d user_key=%s\n",__FUNCTION__,headErrorNo, user_key);

		bPackageOK = false;
	}

	int funcid = m_hsMsgPackage->GetFunction();
	if(funcid != 3001 && funcid != 3003 && funcid != 3004)//打印回调功能号。3001打印的话，太多,忽略。
	{
		my_log("\t%s funcid=%d\n",__FUNCTION__, funcid);
	}

	switch (funcid)
	{
	case H5SDK_MSG_SNAPSHOT://行情快照3001
		if(bPackageOK)
		{
			if (m_hsMsgPackage->GetPacketType() == PUSH)
			{
			//	my_log("\t行情快照主推:\n");//主推处理
			}
			else
			{
				my_log("\t行情快照.异步返回:\n");//请求命令
			}
			MyEnvironment::GetHqSdkUtil()->parse_snapshot(m_hsMsgPackage, this->m_timeReceived);
		}
		else
		{

		}

		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Snapshot);
		break;
	case H5SDK_MSG_L2_TRANSCATION://逐笔成交3003
		if(bPackageOK)
		{
			if (m_hsMsgPackage->GetPacketType() == PUSH)
			{
				my_log("\t逐笔成交主推:\n");//主推处理
			}
			else
			{
				my_log("\t逐笔成交.异步返回:\n");//请求命令
			}
			MyEnvironment::GetHqSdkUtil()->parse_l2_order(m_hsMsgPackage, true);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_L2_Transcation);
		break;
	case H5SDK_MSG_L2_ORDER://逐笔委托3004
		if(bPackageOK)
		{
			if (m_hsMsgPackage->GetPacketType() == PUSH)
			{
				my_log("\t逐笔委托主推:\n");//主推处理
			}
			else
			{
				my_log("\t逐笔委托.异步返回:\n");//请求命令
			}
			MyEnvironment::GetHqSdkUtil()->parse_l2_order(m_hsMsgPackage, true);//与逐笔成交的处理一样。!!!
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_L2_Order);
		break;
	case H5SDK_MSG_MARKET_TYPES: // 市场分类信息
		if(bPackageOK)
		{
			my_log("\t市场分类信息.异步返回:\n");
			MyEnvironment::GetHqSdkUtil()->parse_market_types(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Market_Types);
		break;
	case H5SDK_MSG_TREND://分时
		{
			my_log("\t分时.异步返回:\n");
			MyEnvironment::GetHqSdkUtil()->parse_trend(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Trend);
		break;
	case H5SDK_SERVER_INFO://服务器信息.市场初始化，通知。所以，这里，要通知其他线程，做重新订阅的动作。
		if(bPackageOK)
		{
			my_log("\t服务器信息.异步返回:\n");
			MyEnvironment::GetHqSdkUtil()->parse_server_info(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Server_Info);
		break;
	case H5SDK_MSG_SUBSCRIBE://快照.订阅回应.断线重连，SDK会自动订阅.
		if(bPackageOK)
		{
			my_log("\t订阅.异步返回:\n");
			MyEnvironment::GetHqSdkUtil()->parse_subscribe(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Subscribe);
		break;
	case H5SDK_MSG_SUBSCRIBE_L2_TRANSCATION://逐笔委托.订阅回应.断线重连，SDK会自动订阅.
		if(bPackageOK)
		{
			my_log("\t订阅.异步返回:\n");
			MyEnvironment::GetHqSdkUtil()->parse_subscribe_l2_transcation(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Subscribe_L2_Transcation);
		break;
	case H5SDK_MSG_SUBSCRIBE_L2_ORDER://逐笔委托.订阅回应.断线重连，SDK会自动订阅.
		if(bPackageOK)
		{
			my_log("\t订阅.异步返回:\n");
			MyEnvironment::GetHqSdkUtil()->parse_subscribe_l2_order(m_hsMsgPackage);
		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Subscribe_L2_Order);
		break;
	case H5SDK_MSG_CANDLE_BY_OFFSET://K线回应.
		if(bPackageOK)
		{
			my_log("\tK线.异步返回:\n");
			MyEnvironment::GetHqSdkUtil()->parse_k_line(m_hsMsgPackage, this->m_timeReceived);
		}
		else
		{

		}
		MyEnvironment::PostMainMessage(Command_SdkCallback, SdkCallback_Candle_By_Offset);
		break;
	default:
		{
			//其他业务处理;
			my_log("\t数据包.未处理. id=%d\n", funcid);
		}
	}
}
/*///////////////////////////////////////////////////////////////////////////////
	SDK回调的数据缓冲
///////////////////////////////////////////////////////////////////////////////*/
CSdkPackageQueue::CSdkPackageQueue()
{

}
CSdkPackageQueue::~CSdkPackageQueue()
{
	MyAutoLock lock(m_mutex);

	list<CSdkPackage *>::iterator it;
	for(it = m_listSdkPackage.begin(); it != m_listSdkPackage.end(); it ++)
	{
		delete *it;
	}
	m_listSdkPackage.clear();
}

/*
	存入缓冲
*/
void CSdkPackageQueue::Push(IHsCommMessage* hsMsgPackage)
{
	if(hsMsgPackage == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	MyAutoLock lock(m_mutex);
	CSdkPackage *item = new CSdkPackage(hsMsgPackage);
	m_listSdkPackage.push_back(item);
}

/*
	从缓冲取出.
	取出的指针，需要手动删除
*/
CSdkPackage *CSdkPackageQueue::Pop(void)
{
	MyAutoLock lock(m_mutex);
	if(m_listSdkPackage.size() > 0)
	{
		CSdkPackage *pPackage = *m_listSdkPackage.begin();
		m_listSdkPackage.pop_front();
		return pPackage;
	}
	return NULL;
}

/*///////////////////////////////////////////////////////////////////////////////////////////////////
	SDK缓冲数据处理线程
///////////////////////////////////////////////////////////////////////////////////////////////////*/

/*
	sdk数据包，存到缓冲中
*/
void SdkBufferHandler::Store2Buffer(IHsCommMessage* hsMsgPackage)
{
	if(hsMsgPackage == NULL)
	{
		printf("Error : Shouldn't run in, please check your codes.");
		return ;
	}

	m_sdkPackageQueue.Push(hsMsgPackage);
	Active();
}

CSdkPackage* SdkBufferHandler::GetFromBuffer()
{
	return m_sdkPackageQueue.Pop();
}
/*
	线程入口
*/
int SdkBufferHandler::MainFun()
{
	while(1)
	{
		if(m_bExit)
			break;

		CSdkPackage *item = GetFromBuffer();
		if(item)
		{
			item->Handle();
			delete item;
		}
		else
		{
			if(! IsActive(-1))//等待缓冲中放入新包。
				break;//m_bExit==true;
		}
	}
	return 0;
}