///	��ܲ��
//	��־����ӿ�
#define SID_LOG				    	    "com.hundsun.fbase.log"
//	����ⱨ���ӿ�(ֻ���ṩ��������Ҫ�õ�)
#define SID_F2PACKSVR				"com.hundsun.fbase.f2packsvr"
#define SID_F2PACKER				"com.hundsun.fbase.f2packer"
#define SID_F2UNPACKER				"com.hundsun.fbase.f2unpacker"
//	����4�������÷���ӿ�
#define SID_RCFGOBJ			"com.hundsun.fbase.rcfgobj"
#define SID_WCFGOBJ			"com.hundsun.fbase.wcfgobj"
#define SID_CFGOBJMAKER		"com.hundsun.fbase.cfgobjmaker"
#define SID_CFGSVR			"com.hundsun.fbase.config"
//	�����ӿ�(ͨ������,���Ի�����еĽӿ�)
#define SID_H5_CORE  "com.hundsun.fbase.f2core"


////////////////	ͨ�ýӿ�	/////////////////////
//	�ṩ��ʱ����Ĳ���ӿ���	��̬����:	fsc_timer
#define SID_TIMER	"com.hundsun.fbase.timer"
//	����ʱ����ʱ���õĽӿ�
#define SID_TIMER_DEALER	"com.hundsun.fbase.timer_dealer"
//	��Ϣ����ӿ�(һ����˵,���з������������ӿڶ��Ǹýӿ�,�����Զ����ṩ�����ӿ��ṩ�ض�����)
#define SID_IHQMESSAGE_SERVICE	"com.hundsun.fbase.h5messageservice"
//	ͨ��������	��̬����: fsc_hscomm
#define SID_HSCOMM_ADAPTER	"com.hundsun.fbase.commadapter"
#define SID_HSCOMM_SVR "com.hundsun.fbase.hscomm"				//	ͨ�ŷ���,�ýӿ��ڲ����Զ����ṩSID_HQCOMM_ADAPTER����ͨ�����ҵ��
//	��Ϣ�����ӿ�	����:	fsc_hscommsg
#define SID_HSCOMM_MESSAGEFACTORY		"com.hundsun.fbase.hscommessagefactory"	



//	ͬ�����ýӿ�
#define SID_H5_SYN_CALL "com.hundsun.h5.syncall"
//      ����Դ��ʼ��֪ͨע����
#define SID_H5D_INITNOTIFY_REGISTER "com.hundsun.h5ds.initnotify"

//	sid��������:
/*
	���������������Դ���������õĲ��:SID_H5_��ͷ
	���������:SID_H5HQ_	��ͷ
	����Դ:		 SID_H5DS_	��ͷ
*/

////////////////	���������Ҫ�Ĳ��	//////////////////
//	Э���������ӿ�	��̬����: h5_hsproto_adapter
#define SID_H5_PROTOCOL_ADAPTER	"com.hundsun.h5.protocoladapter"
// �����ڲ�Э��Ľ�������
#define SID_H5_PROTO_SVR "com.hundsun.h5.protosvr"		//	�����ṩSID_H5_PROTOCOL_ADAPTER�ӿ�

//	������־���	����: h5_quotelog
#define SID_H5_QUOTELOG	"com.hundsun.h5.quotelog"
//	������־����ӿ�	
#define SID_H5_QUOTELOG_INTERFACE	"com.hundsun.h5.quotelog.interface"


//	����������ӿ�	����: h5_dispatcher
#define SID_H5_DISPATCHER	"com.hundsun.h5.dispatcher"
//	�¼�ע��ӿ�
#define SID_H5_REGISTER	"com.hundsun.h5.register"
//	����ӿ�				����: h5hq_cache
#define SID_H5HQ_CACHE "com.hundsun.h5hq.cache"

//	���ݺ��Ĳ�ӿ�	����: h5_datacore
#define SID_H5_DATA_CORE		"com.hundsun.h5.data_core"

// L1 dcdp 					����: h5hq_l1_dcdp
#define SID_H5HQ_L1_DCDP "com.hundsun.h5hq.l1_dcdp"
// L1 dcdp data query
#define SID_H5HQ_L1DCDP_QUERY "com.hundsun.h5hq.l1dcdp_query"
//L2  dcdp 					����: h5hq_l2_dcdp
#define SID_H5HQ_L2_DCDP     "com.hundsun.h5hq.l2_dcdp"
//DDE dcdp
#define SID_H5HQ_DDE_DCDP     "com.hundsun.h5hq.dde_dcdp"
//DDE�����ѯ�ӿ�
#define SID_H5HQ_DDE_DCDP_QUERY   "com.hundsun.h5hq.Ddedcdp_query"		//add by hegh2011-11-10
//
#define SID_H5HQ_BLOCK_DCDP          "com.hundsun.h5hq.block_dcdp"
// ����DCDP
#define SID_H5HQ_US_STOCK_DCDP   "com.hundsun.h5hq.usstock.dcdp"

//L2DCDP֧��HQ4.0�������ѯ�ӿ�
#define SID_H5HQ_L2_DCDP_QUERY   "com.hundsun.h5hq.l2dcdp_query"
//HKEx DCDP ������h5hq_hk_dcdp
#define SID_H5HQ_HK_DCDP	"com.hundsun.h5hq.hkex_dcdp"
//�Ϻ��ƽ�DCDP
#define SID_H5HQ_SGE_DCDP	"com.hundsun.h5hq.sge_dcdp"
//HKEx �����ѯ�ӿ�
#define SID_H5HQ_HK_DCDP_QUERY	"com.hundsun.h5hq.hkex_dcdp_query"
// ȫ��ָ��DCDP
#define SID_H5HQ_GLBINDEX_DCDP	"com.hundsun.h5hq.glbindex_dcdp"
// ���DCDP
#define SID_H5HQ_FX_DCDP	"com.hundsun.h5hq.fx_dcdp"
// �ֻ�DCDP
#define SID_H5HQ_SPOT_DCDP	"com.hundsun.h5hq.spot_dcdp"

// ������ȨDCDP
#define SID_H5HQ_STOCK_OPTION_DCDP	"com.hundsun.h5hq.stock_option_dcdp"

// �ڻ���ȨDCDP
#define SID_H5HQ_FUTURES_OPTION_DCDP	"com.hundsun.h5hq.futures_option_dcdp"

// ���м�ծȯDCDP
#define SID_H5HQ_INTERBANK_DCDP	"com.hundsun.h5hq.interbank_dcdp"

//��չָ���г�
#define SID_H5HQ_EXT_DCDP	"com.hundsun.h5hq.ext_dcdp"

//�����ڻ�DCDP
#define SID_H5HQ_FRGNFUTURES_DCDP	"com.hundsun.h5hq.frgnfutures_dcdp"

//�ڻ�����DCDP	by maxy
#define SID_H5HQ_ARBFUTURES_DCDP        "com.hundsun.h5hq.arbfutures_dcdp"	

// ���߾���DCDP			����:	h5hq_shortwizard_dcdp
#define SID_SHORTWIZARD_DCDP	"com.hundsun.h5hq.shortwizard_dcdp"

/// ÿ�����������DCDP��Ҫʵ�ֵĽӿ�
#define SID_H5HQ_DCDP_QUERY	"com.hundsun.h5hq.dcdp_query"


// BP����ڲ��ṩҵ����Ľӿ�,	��������ԴBPҲ��Ҫ�ṩ�ýӿ�					
#define SID_H5_BIZPROCESS	"com.hundsun.h5hq.bizprocess"
//	�����������BP����
#define SID_H5HQ_BIZ_SVR	"com.hundsun.h5hq.bizsvr"		//	����	h5hq_bp

//	���Ľӿ�				����:	h5_subscribe
#define SID_H5_SUBSCRIBE	"com.hundsun.h5.subscribe"



// ���Э��������		����:	h5_monitor
#define SID_H5_MONITOR "com.hundsun.h5.monitor"
// L2תL1������
#define SID_H5_L2TOL1_ADAPTER "com.hundsun.h5.l2tol1_adapter" // h5_l2tol1_adapter


// Ȩ�޴�����			����:	h5hq_auth
#define SID_H5HQ_AUTH "com.hundsun.h5hq.auth"		// �����ṩSID_H5HQ_AUTH_ADAPTER�ӿ�
// Ȩ�޴�������ӿ�
#define SID_H5HQ_AUTH_ADAPTER		"com.hundsun.h5hq.authadapter"

//����ԴDCDP				����:	h5ds_dcdp
#define SID_H5DS_DCDP    "com.hundsun.h5ds.dcdp"
//
#define SID_H5DS_DCDP_EXT    "com.hundsun.h5ds.dcdpext"


//����ԴBP					����:	h5ds_bp
#define SID_H5DS_BP                    "com.hundsun.h5ds.bizprocess"

//����ҵ������	����:	h5hq_maintain_bp
#define SID_H5HQ_MAINTAIN_BP		"com.hundsun.h5hq.maintain_bp"

//�������ݼӹ�������	����:	h5hq_maintain_dp
#define SID_H5HQ_MAINTAIN_DP		"com.hundsun.h5hq.maintain_dp"


///////	����Դ����������
//�ڻ���������� ����: h5ds_futures
#define SID_H5DS_FUTURES_ADAPTER "com.hundsun.h5ds.futures"					//	h5ds_futures
//�ڻ���������� ����: h5ds_futures
#define SID_H5DS_CFFEXL2_ADAPTER "com.hundsun.h5ds.cffexl2_adapter"	

//�Ϻ�L1���������
#define SID_H5DS_SHL1_ADAPTER    "com.hundsun.h5ds.shl1_adapter"		//	h5ds_shl1_adapter
//����L1���������
#define SID_H5DS_SZL1_ADAPTER    "com.hundsun.h5ds.szl1_adapter"		//	h5ds_szl1_adapter
//�Ϻ�L2���������
#define SID_H5DS_SHL2_ADAPTER    "com.hundsun.h5ds.shl2_adapter"		//	h5ds_shl2_adapter
//����L2���������
#define SID_H5DS_SZL2_ADAPTER    "com.hundsun.h5ds.szl2_adapter"		//	h5ds_szl2_adapter
//�۹�������
#define SID_H5DS_HK_ADAPTER      "com.hundsun.h5ds.hk_adapter"			//	h5ds_hk_adapter
//�۹�ָ��������
#define SID_H5DS_HKINDEX_JRJ_ADAPTER "com.hundsun.h5ds.hkindex_jrj_adapter"		//  h5ds_hkindex_jrj_adapter
//��չ����������
#define SID_H5DS_EXTENDED_ADAPTER "com.hundsun.h5ds.extended_adapter"           //      h5ds_extended_adapter
//ת��Դ������
#define SID_H5DS_FORWARD_ADAPTER  "com.hundsun.h5ds.forward_adapter"            //      h5ds_forward_adapter
//�����ڻ�������
#define SID_H5DS_FRGNFUTURES_ADAPTER "com.hundsun.h5ds.frgnfutures_adapter"		//  h5ds_frgnfutures_adapter
//OTC������
#define SID_H5DS_OTC_ADAPTER  "com.hundsun.h5ds.otc_adapter"

//��ȷ������
#define SID_DEPTH_ANALYSIS     "com.hundsun.h5.depth_analysis_adapter" 

// ��Ȩ������
#define SID_H5DS_OPTION_ADAPTER "com.hundsun.h5ds.option_adapter"

//DataFeed
#define SID_H5DS_DATA_FEED      "com.hundsun.h5ds.datafeed"

//TestPlugin
#define SID_TEST_PLUGIN      "com.hundsun.test_plugin"

// ���м�ծȯ(inter-bank bond) ����Դ ������
#define SID_H5DS_IBB_ADAPTER "com.hundsun.h5ds.ibb_adapter"

// �����Ļ���Ȩ����������Դ������
#define SID_H5DS_CAE_ADAPTER "com.hundsun.h5ds.cae_adapter"

// ������Ʒ����������Դ������
#define SID_H5DS_HAIXI_ADAPTER "com.hundsun.h5ds.haixi_adapter"

// �۽��� Orion Market Data Platform ����Դ������
#define SID_H5DS_OMD_ADAPTER "com.hundsun.h5ds.omd_adapter"

//------------------- XINHUA08������SID ------ZXW---20110701---------
#define SID_H5DS_SHL1_ADAPTER_XH08      "com.hundsun.h5ds.shl1_adapter.xh08"
#define SID_H5DS_SZL1_ADAPTER_XH08      "com.hundsun.h5ds.szl1_adapter.xh08"
#define SID_H5DS_FURTURES_ADAPTER_XH08  "com.hundsun.h5ds.futures_adapter.xh08"
#define SID_H5DS_HK_ADAPTER_XH08        "com.hundsun.h5ds.hk_adapter.xh08"
#define SID_H5DS_GOLD_ADAPTER_XH08      "com.hundsun.h5ds.gold_adapter.xh08"
#define SID_H5DS_GLOBAL_INDEX_ADAPTER_XH08 "com.hundsun.h5ds.global_index_adapter.xh08"
#define SID_H5DS_FX_ADAPTER_XH08        "com.hundsun.h5ds.fx_adapter.xh08"

#define SID_H5DS_HONGHUI_ADAPTER        "com.hundsun.h5ds.honghui_adapter"
//�ֻ�������
#define SID_H5DS_SPOT_ADAPTER     "com.hundsun.h5ds.spot_adapter"


// DCDP���	����:	h5hq_dcdp_mngr
#define SID_H5HQ_DCDP_MANAGER "com.hundsun.h5hq.dcdp_manager"		//	h5hq_dcdpmanager �����ӿ�
#define SID_H5_DCDP_CORE	"com.hundsun.h5.dcdpcore"						//	������������� ����DCDP �Ĺ���
#define SID_H5_DCDP_DATA	"com.hundsun.h5.dcdpdata"						// dcdp�������ݲ�ѯ�ӿڽӿ�	BPʹ��

// ��������
#define SID_H5HQ_QUOTA_CENTER "com.hundsun.h5hq.quota_center"
#define SID_H5HQ_QUOTA_SERVICE "com.hundsun.h5hq.quota_service"

#define SID_QS_CLIENT "com.hundsun.qs_client"
#define SID_QS_SERVER "com.hundsun.qs_server"
#define SID_QS_DEMO   "com.hundsun.qs_demo"

//�����
#define SID_H5DS_BLOOMBERG_ADAPTER  "com.hundsun.h5ds.bloomberg_adapter"

//�������
//ѹ�������ܲ��Բ�� ����Ϊ:h5test_hqtest
#define SID_H5TEST_HQTEST "com.hundsun.h5test.hqtest"
//Level2�����ھ�����Ŀǰ�ɺι�����ʹ�ã���ǰ����ʽ�����汾�������˲����
#define SID_H5_DATA_ANALYSE_DP          "com.hundsun.h5.analyse_dp"
#define SID_H5_DATA_ANALYSE_QUERY   "com.hundsun.hq5.analyse_dp_query"


