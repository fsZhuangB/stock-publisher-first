#include <stdlib.h>
#include <stdio.h>
#include <sstream> 
#include <fstream>
#include <map>
#include "Config.h"
#include <string.h>
#include "json/json.h"

#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;


Config::Config(string path) {
    loadConfig(path);
}

Config& Config::getInstance(string path){
    static Config config(path);
    return config;
}

void Config::loadConfig(string cfg_path){
    ifstream infile(cfg_path.c_str());
    if (!infile.is_open())
    {
        fprintf(stderr,"Opened config file error! Maybe the file %s doesn't exist.\n",cfg_path.c_str());
        exit(1);
    }else {
        string line;
        while (getline(infile, line)){
            unsigned int len = line.length();
            if (len== 0 || line.at(0) == '#'){
                continue;
            }
            unsigned int p = line.find("=");
            if(p == string::npos){
                fprintf(stderr,"Config item error or empty: %s\n",line.c_str());
                continue;
            }
            kv[line.substr(0,p)] = line.substr(p+1,len-p-1);
        }
        infile.close();
        md_out_dir = kv["md_out_dir"];
        md_file_prefix = kv["md_file_prefix"];
        md_file_suffix = kv["md_file_suffix"];
        
        md_adapter = kv["md_adapter"];
        md_type = kv["md_type"];
        route_key = kv["route_key"];
        md_stream_dir = kv["md_stream_dir"];
        md_url = kv["md_url"];
        stringstream(kv["md_port"]) >> md_port;
        md_broker_id = kv["md_broker_id"];
        md_user_name = kv["md_user_name"];
        md_password = kv["md_password"];
        local_ip = kv["local_ip"];
        stringstream(kv["local_port"]) >> local_port;
        trade_query_ip = kv["trade_query_ip"];
        stringstream(kv["trade_query_port"]) >> trade_query_port;
        
        trade_adapter = kv["trade_adapter"];
        trade_stream_dir = kv["trade_stream_dir"];
        trade_url = kv["trade_url"];
        stringstream(kv["trade_port"]) >> trade_port;
        trade_broker_id = kv["trade_broker_id"];
        trade_user_name = kv["trade_user_name"];
        trade_investor_id = kv["trade_investor_id"];
        trade_password = kv["trade_password"];
        exchange = kv["exchange"];
        auth_code = kv["auth_code"];
        md_queue_prefix = kv["md_queue_prefix"];
        strategy_names = kv["strategy_names"];
        stringstream(kv["strategy_factor"]) >> strategy_factor;
        
    }
}

const string& Config::mdOutDir() const{ return md_out_dir;}
const string& Config::mdFilePrefix() const{ return md_file_prefix;}
const string& Config::mdFileSuffix() const{ return md_file_suffix;}

const string& Config::tradeAdapter() const{ return trade_adapter;}
const string& Config::tradeStreamDir() const{ return trade_stream_dir;}
const string& Config::tradeUrl() const{ return trade_url;}
const unsigned int& Config::tradePort() const{return trade_port;}
const string& Config::tradeBrokerId() const{return trade_broker_id;};
const string& Config::tradeUserName() const{ return trade_user_name;};
const string& Config::tradeInvestorId() const{ return trade_investor_id;};
const string& Config::tradePassword() const{ return trade_password;};

const string& Config::mdAdapter() const{ return md_adapter;}
const string& Config::mdType() const{ return md_type;}
const string& Config::routeKey() const{ return route_key;}
const string& Config::mdStreamDir() const{ return md_stream_dir;}
const string& Config::mdUrl() const{ return md_url;}
const unsigned int& Config::mdPort() const{ return md_port;}
const string& Config::mdBrokerId() const{return md_broker_id;};
const string& Config::mdUserName() const{ return md_user_name;};
const string& Config::mdPassword() const{ return md_password;};

const string& Config::localIp() const{ return local_ip;}
const unsigned int& Config::localPort() const{ return local_port;}
const string& Config::tradeQueryIp() const{return trade_query_ip;};
const unsigned int& Config::tradeQueryPort()  const{return trade_query_port;};
const string& Config::exchangeId() const { return exchange;}
const string& Config::authCode() const {return auth_code;}
const string& Config::mdQueuePrefix() const { return md_queue_prefix;};
const string& Config::strategyNames() const { return strategy_names;};
const float&  Config::strategyFactor() const { return strategy_factor;};









/*
{
    "risk_control" : [
        {
            "type" : 0, "per_val" : "1100000", "total_val" : "3300000",
            "rate_ordmum" : 100, "total_ordmum" : 20000, 
            "rate_cancelmum" : 100, "total_cancelmum" : 500
        },
        {
            "type" : 1, "per_val" : "0", "total_val" : "0", 
            "rate_ordmum" : 1000, "total_ordmum" : 30000, 
            "rate_cancelmum" : 1000, "total_cancelmum" : 30000
        },
        {
            "type" : 2, "per_val" : "0", "total_val" : "0", 
            "rate_ordmum" : 1000, "total_ordmum" : 50000, 
            "rate_cancelmum" : 1000, "total_cancelmum" : 50000
        }
    ],
    "strategy_proc" : [
        {"name" : "grab1", "index":0, "type" : 0 },
        {"name" : "grab2", "index":1, "type" : 0 },
        {"name" : "close_down_limit3", "index":2, "type" : 1 },
        {"name" : "close_down_limit3", "index":3, "type" : 2 }                        
    ],
    "rtn_memqueue_len" : 65536,
    "req_memqueue_len" : 4096,
    "md_queue_prefix" : "stock_md_p",
    "driver" : "WFJ1EPRD"
}
*/

Json::Value ReadConfigFromFile(const char* fn, const char* key, std::string* err) {
    FILE* handle = fopen(fn, "r");
    if (handle == 0) {
		if (err != 0) {
			*err = "File doesn't exists";
		}        
        return Json::Value();
    }

    fseek(handle, 0, SEEK_END);	
    long fs = ftell(handle);
    fseek(handle, 0, SEEK_SET);

	std::string cfg(fs, ' ');
    if ((long)fread((char*)cfg.c_str(), 1, fs, handle) != fs) {
		if (err != 0) {
			*err = "Read file failed";
		}
		return Json::Value();
    }
	
	Json::Reader reader;
	Json::Value rootValue;
	if (!reader.parse(cfg, rootValue)) {
		if (err != 0) {
			*err = reader.getFormatedErrorMessages().c_str();
		}
		return Json::Value();
	}

	if (key == 0) {
		return rootValue;
	}

	if (rootValue.isMember(key)) {
		Json::Value& ret = rootValue[key];
		if (!ret.isNull()) {
			return ret;
		}
	}

	if (err != 0) {
		*err = "Object name not found";
	}
	return Json::Value();
}

bool TradeModeuleConfig::Load(const char* configFile) {

    std::string readError;        
    Json::Value rootValue = ReadConfigFromFile(configFile, 0, &readError);
    if (rootValue.isNull()) {
        fprintf(stdout, "read config file %s failed: %s\n", configFile, readError.c_str());
        return false;
    }

    if (!rootValue.isMember("trade_instance") || !rootValue.isMember("MongoDBConfig"))
    {
        fprintf(stdout, "config error: key \"trade_instance\" or \"MongoDBConfig\" missing in file %s, please check.\n", configFile);
        return false;
    }

    auto trade_instance = rootValue["trade_instance"].asString();
    auto mongodb_config = rootValue["MongoDBConfig"];

    if (!mongodb_config.isMember("connectString") 
        || !mongodb_config.isMember("tradeDB")
        || !mongodb_config.isMember("tradeCollection")
        || !mongodb_config.isMember("strategyDB")
        || !mongodb_config.isMember("strategyCollection"))
    {
        fprintf(stdout, "config error: key \"connectString\", \"tradeDB\", \"tradeCollection\", \"strategyDB\" or \"strategyCollection\" missing in file %s, please check.\n", configFile);
        return false;
    }

    auto conn_string = mongodb_config["connectString"].asString();
    auto trade_db_name = mongodb_config["tradeDB"].asString();
    auto trade_coll_name = mongodb_config["tradeCollection"].asString();
    auto strategy_db_name = mongodb_config["strategyDB"].asString();
    auto strategy_coll_name = mongodb_config["strategyCollection"].asString();

    mongocxx::instance instance{}; // This should be done only once.
    mongocxx::uri uri(conn_string);
    mongocxx::client client(uri);
    //读取trade_instance配置
    {
        mongocxx::database tradedb = client[trade_db_name];
        mongocxx::collection trade_coll = tradedb[trade_coll_name];
        mongocxx::options::find opts;
        opts.sort(make_document(kvp("_id", -1)));
        opts.limit(1);
        //bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
        auto cursor = trade_coll.find(make_document(kvp("instance_name", trade_instance)), opts);

        if (cursor.begin() == cursor.end())
        {
            fprintf(stdout, "config error: no config result queried from db, please check db.\n");
            return false;
        }

        auto&& doc = *(cursor.begin());
        std::string config = bsoncxx::to_json(doc);
        Json::Reader reader;
        Json::Value rootCfg;
        if (!reader.parse(config, rootCfg)) {
            fprintf(stdout, "parse config failed: %s\n", reader.getFormatedErrorMessages().c_str());
            return false;
        }

        fprintf(stdout, "config queried from db:\n %s\n", rootCfg.toStyledString().c_str());

        m_rtn_memqueue_len = 0;
        m_rtn_memqueue_len = rootCfg["rtn_memqueue_len"].asInt();

        m_req_memqueue_len = 0;
        m_req_memqueue_len = rootCfg["req_memqueue_len"].asInt();

        m_driver = rootCfg["driver"].asString();

        fprintf(stdout, "m_rtn_memqueue_len %d, m_req_memqueue_len %d , m_driver %s\n", m_rtn_memqueue_len, m_req_memqueue_len, m_driver.c_str());
    }

    //读取strategy_instance配置
    {
        mongocxx::database strategydb = client[strategy_db_name];
        mongocxx::collection strategy_coll = strategydb[strategy_coll_name];
        Json::Value rootCfg;
        //step1. get latest trade_date for specified trade_instance
        {
            mongocxx::options::find opts;
            opts.sort(make_document(kvp("trade_date", -1)));
            opts.limit(1);
            //bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            auto cursor = strategy_coll.find(make_document(kvp("trade_instance", trade_instance)), opts);

            if (cursor.begin() == cursor.end())
            {
                fprintf(stdout, "config error: no config result for trade instance %s queried from db, please check db.\n", trade_instance.c_str());
                return false;
            }

            auto&& doc = *(cursor.begin());
            std::string config = bsoncxx::to_json(doc);
            Json::Reader reader;
            if (!reader.parse(config, rootCfg)) {
                fprintf(stdout, "parse config failed: %s\n", reader.getFormatedErrorMessages().c_str());
                return false;
            }
            auto trade_date = rootCfg["trade_date"].asString();
            fprintf(stdout, "latest trade date %s for trade instance %s queried from db\n", trade_date.c_str(), trade_instance.c_str());

            //step2. get all rows with specified trade_instance and trade_date
            {
                mongocxx::options::find opts;
                opts.projection(make_document(kvp("trade_date", 1), kvp("execute_strategy", 1), kvp("account", 1), kvp("trade_config", 1)));
                opts.sort(make_document(kvp("account", 1), kvp("execute_strategy", 1)));
                //bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
                auto cursor = strategy_coll.find(make_document(kvp("trade_date", trade_date), kvp("trade_instance", trade_instance)), opts);

                if (cursor.begin() == cursor.end())
                {
                    fprintf(stdout, "config error: no config result for trade instance %s queried from db, please check db.\n", trade_instance.c_str());
                    return false;
                }

                for (auto& doc: cursor)
                {
                    std::string config = bsoncxx::to_json(doc);
                    Json::Reader reader;
                    Json::Value  strategy_proc_cfg;
                    if (!reader.parse(config, strategy_proc_cfg)) {
                        fprintf(stdout, "parse config failed: %s\n", reader.getFormatedErrorMessages().c_str());
                        return false;
                    }

                    fprintf(stdout, " %s\n", strategy_proc_cfg.toStyledString().c_str());
                    StrategyConfig  slc;
                    slc.m_strategy_proc = strategy_proc_cfg["execute_strategy"].asString()+"_"+strategy_proc_cfg["account"].asString();

                    //work around solution, should be removed
                    //if (slc.m_strategy_proc.find("grab_p1") != std::string::npos)
                    //{
                    //    slc.m_priority = 0;
                    //} 
                    //else if(slc.m_strategy_proc.find("grab_p2") != std::string::npos)
                    //{
                    //    slc.m_priority = 1;
                    //}
                    //else if (slc.m_strategy_proc.find("enter_ivol") != std::string::npos)
                    //{
                    //    slc.m_priority = 6;
                    //}
                    //else if (slc.m_strategy_proc.find("enter") != std::string::npos)
                    //{
                    //    slc.m_priority = 2;
                    //}
                    //else if (slc.m_strategy_proc.find("exit_down_limit") != std::string::npos)
                    //{
                    //    slc.m_priority = 4;
                    //}
                    //else if (slc.m_strategy_proc.find("exit") != std::string::npos)
                    //{
                    //    slc.m_priority = 3;
                    //}
                    //else if(slc.m_strategy_proc.find("t0") != std::string::npos)
                    //{
                    //    slc.m_priority = 5;
                    //}

                    const Json::Value& risk_control_cfg = strategy_proc_cfg["trade_config"]["risk_param"];
                    if (risk_control_cfg.isMember("rate_ordmum"))
                    {
                        slc.m_rate_ordnum = risk_control_cfg["rate_ordmum"].asUInt();
                    }
                    
                    if (risk_control_cfg.isMember("total_ordmum"))
                    {
                        slc.m_total_ordnum = risk_control_cfg["total_ordmum"].asUInt();
                    }
                    
                    if (risk_control_cfg.isMember("rate_cancelmum"))
                    {
                        slc.m_rate_cancelnum = risk_control_cfg["rate_cancelmum"].asUInt();
                    }
                    
                    if (risk_control_cfg.isMember("total_cancelmum"))
                    {
                        slc.m_total_cancelnum = risk_control_cfg["total_cancelmum"].asUInt();
                    }
                    
                    if (risk_control_cfg.isMember("per_val"))
                    {
                        slc.m_per_val = std::strtoul(risk_control_cfg["per_val"].asString().c_str(), NULL, 10);
                    }
                    
                    if (risk_control_cfg.isMember("total_val"))
                    {
                        slc.m_total_val = std::strtoul(risk_control_cfg["total_val"].asString().c_str(), NULL, 10);
                    }
                    
                    //如果是共享风控参数
                    if (risk_control_cfg.isMember("shared_num"))
                    {
                        slc.m_shared_num = risk_control_cfg["shared_num"].asInt();
                        auto found = false;
                        int type = 0;
                        for (size_t idx = 0; idx < m_strategy_config.size(); idx++)
                        {
                            if (slc.m_shared_num == m_strategy_config[idx].m_shared_num)
                            {
                                found = true;
                                type = idx;
                                break;
                            }
                        }

                        //如果之前的没有定义过，则是首次定义，加入到风控参数数组和策略类型数组中去
                        if (!found)
                        {
                            slc.m_type = m_strategy_config.size();
                            m_strategy_config.emplace_back(slc);
                        }
                        else //如果之前已经定义过，则类型数组中加入即可
                        {
                            slc.m_type = type;
                            slc.m_rate_ordnum = m_strategy_config[type].m_rate_ordnum;
                            slc.m_total_ordnum = m_strategy_config[type].m_total_ordnum;
                            slc.m_rate_cancelnum = m_strategy_config[type].m_rate_cancelnum;
                            slc.m_total_cancelnum = m_strategy_config[type].m_total_cancelnum;
                            slc.m_per_val = m_strategy_config[type].m_per_val;
                            slc.m_total_val = m_strategy_config[type].m_total_val;
                            m_strategy_config.emplace_back(slc);
                        }
                    }
                    else
                    {
                        slc.m_type = m_strategy_config.size();
                        m_strategy_config.emplace_back(slc);
                    }
                }

                ////special handling
                //std::sort(m_strategy_config.begin(), m_strategy_config.end(), [](const StrategyConfig& lhs, const StrategyConfig& rhs)
                //{
                //    return lhs.m_priority < rhs.m_priority;
                //});
            }
        }
    }

    return true;     
}

TradeModeuleConfig::TradeModeuleConfig()
{
    Load("./trademodule.cfg");
}


const TradeModeuleConfig& TradeModeuleConfig::getInstance() 
{
    static TradeModeuleConfig s_TradeModeuleConfig;
    return s_TradeModeuleConfig;
}