//
// Created by fszhuangb on 6/7/20.
//
#include "../include/h5md/h5sdk/h5sdk.h"
#include "../include/h5md/h5sdk/h5sdk_export.h"
#include    <sutil/logger/spk_log.h>
#include "main_environment.h"
#include <string>
#include "datatype.h"
#include "queue.h"
#include "md_publisher.h"
#include "utility.h"


using namespace std;
#define SHARED_QUEUE_SIZE 8192
static int queue_shm_fd = 0;
static int data_shm_fd = 0;
static struct vrt_queue* _q ;
static PVO* _md_data;
static struct vrt_producer* _p;

static HqSdkUtil *m_pHqSdkUtil; //行情SDK工具类

void init_shm_queue(const Config& config) {
    string queue_data_str = config.mdQueuePrefix();
    string queue_str = queue_data_str + "_queue";
    string queue_producer = queue_data_str + "_producer";
    
    _q = vrt_queue_new (queue_str.c_str(), SHARED_QUEUE_SIZE, sizeof(PVO), &queue_shm_fd);
    _md_data = (PVO*)vrt_data_new(queue_data_str.c_str(), (_q->value_mask + 1)*sizeof(PVO), &data_shm_fd);
    _p = vrt_producer_new(queue_producer.c_str(), 1, _q, 0, true); 
}


void start_md(Config& config)
{
	MyEnvironment env;
    init_shm_queue(config);

    /*////////////////////////////////////////////////////////////////////////////////////
	//Sdk初始化
	////////////////////////////////////////////////////////////////////////////////////*/
	m_pHqSdkUtil = new HqSdkUtil();
	//从文件里获取配置
	if(! m_pHqSdkUtil->ReadConfigure())
	{
		my_log("read configure failed.\n");
		return ;
	}

    //////////////////////////////////////////////////////////////////////////////////////////*/
	//init the SDK, and set call back class
    //////////////////////////////////////////////////////////////////////////////////////////*/
	if(! MyEnvironment::GetHqSdkUtil()->sdk_init())
	{
		my_log("sdk init failed.\n");
		return ;
	}

	my_log("\tBegin SDK session\n");

// finish the login callback
	env.WaitForMessage(Command_SdkCallback, SdkCallback_Login, MyEnvironment::OnLoginOver);

    MyEnvironment::m_listCodes.clear();

}