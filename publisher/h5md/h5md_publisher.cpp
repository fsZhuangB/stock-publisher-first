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

static HqSdkUtil *m_pHqSdkUtil; //����SDK������

void init_shm_queue(const Config& config) {
    string queue_data_str = config.mdQueuePrefix();
    string queue_str = queue_data_str + "_queue";
    string queue_producer = queue_data_str + "_producer";
    
    _q = vrt_queue_new (queue_str.c_str(), SHARED_QUEUE_SIZE, sizeof(PVO), &queue_shm_fd);
    _md_data = (PVO*)vrt_data_new(queue_data_str.c_str(), (_q->value_mask + 1)*sizeof(PVO), &data_shm_fd);
    _p = vrt_producer_new(queue_producer.c_str(), 1, _q, 0, true); 
}

//this tool is used to get SDK 
HqSdkUtil *MyEnvironment::GetHqSdkUtil() //����SDK������
{
	return m_pHqSdkUtil;
}

void start_md(Config& config)
{
    init_shm_queue(config);

    /*////////////////////////////////////////////////////////////////////////////////////
	//Sdk��ʼ��
	////////////////////////////////////////////////////////////////////////////////////*/
	m_pHqSdkUtil = new HqSdkUtil();
	//���ļ����ȡ����
	if(! m_pHqSdkUtil->ReadConfigure())
	{
		my_log("read configure failed.\n");
		return ;
	}

    //////////////////////////////////////////////////////////////////////////////////////////*/
	//��ʼ��SDK
    //////////////////////////////////////////////////////////////////////////////////////////*/
	if(! GetHqSdkUtil()->sdk_init())
	{
		my_log("sdk init failed.\n");
		return ;
	}

    m_listCodes.clear();
    GetHqSdkUtil()->GetCodesInMarket("XSHG.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/);
	GetHqSdkUtil()->GetCodesInMarket("XSHE.ESA.M", &m_listCodes, GetHqSdkUtil()->m_iMaxNumberTest/*ֻȡ��ô��*/);







}