#ifndef _CONFIG_H
#define _CONFIG_H
#include <limits>
#include <string>
#include <map>
#include <vector>
using namespace std;
class Config{
public:
    static Config& getInstance(string path="./config.cfg");
private:
    Config(string path);
    Config(Config const&) = delete;
    void operator=(Config const&) = delete;
public:
    const string& mdOutDir() const;
    const string& mdFilePrefix() const;
    const string& mdFileSuffix() const;

    const string& mdAdapter() const;
    const string& mdType() const;
    const string& routeKey() const;
    const string& mdStreamDir() const;
    const string& mdUrl() const;
    const unsigned int& mdPort() const;
    const string& mdBrokerId() const;
    const string& mdUserName() const;
    const string& mdPassword() const;

    const string& tradeAdapter() const;
    const string& tradeStreamDir() const;
    const string& tradeUrl() const;
    const unsigned  int& tradePort() const;
    const string& tradeBrokerId() const;
    const string& tradeUserName() const;
    const string& tradeInvestorId() const;
    const string& tradePassword() const;
    const string& localIp() const;
    const unsigned int& localPort() const;
    const string& tradeQueryIp() const;
    const unsigned int& tradeQueryPort() const;
    const int req_memqueue_len() { return std::stoi(kv["req_memqueue_len"]);}
    const int rtn_memqueue_len() { return std::stoi(kv["rtn_memqueue_len"]);}
    const string& exchangeId() const;
    const string& authCode() const;
    const string& mdQueuePrefix() const;
    const string& strategyNames() const;
    const float&  strategyFactor() const;
    const unsigned long max_open_cash(){ return std::stoul(kv["max_open_cash"]);}
    const int per_stock_limit(){ return std::stoi(kv["per_stock_limit"]);}
    const int strategy_md_slice() { return std::stoi(kv["strategy_md_slice"]);}
    const string& db_url() { return kv["db_url"];}
    const string& strategy_types() { return kv["strategy_types"];}
    const string& strategy_per_val() { return kv["strategy_per_val"];}
    const string& strategy_total_val() { return kv["strategy_total_val"];}
    const string& strategy_rate_ordmum() { return kv["strategy_rate_ordmum"];}
    const string& strategy_total_ordmum() { return kv["strategy_total_ordmum"];}
    const string& strategy_rate_cancelmum() { return kv["strategy_rate_cancelmum"];}
    const string& strategy_total_cancelmum() { return kv["strategy_total_cancelmum"];}
    const string& routeKey2()  { return kv["route_key2"];}
    const string& routeKeySH()  { return kv["route_key_sh"];}
    const string& black_list()  { return kv["black_list"];}
    const string& driver()  { return kv["driver"];}
private:
    void loadConfig(string cfg_path);
    map<string,string> kv ;

private:
    ////行情存储配置
    string md_out_dir;
    string md_file_prefix;
    string md_file_suffix;
    //行情相关配置
    string md_adapter;
    string md_type;
    string route_key;
    string md_stream_dir;
    string md_url;
    unsigned int md_port;
    string md_broker_id;
    string md_user_name;
    string md_password;
    string local_ip;
    unsigned int local_port;
    //交易相关配置
    string trade_adapter;
    string trade_stream_dir;
    string trade_url;
    unsigned int trade_port;
    string trade_query_ip;
    unsigned int trade_query_port;
    string trade_broker_id;
    string trade_user_name;
    string trade_investor_id;
    string trade_password;
    string exchange;
    string auth_code;
    string md_queue_prefix;
    string strategy_names;
    float  strategy_factor;
};

struct StrategyConfig {
    std::string m_strategy_proc;
    int m_priority;
    int m_type;
    int m_shared_num;
    uint64_t m_per_val;
    uint64_t m_total_val;
    uint32_t m_rate_ordnum;
    uint32_t m_total_ordnum;
    uint32_t m_rate_cancelnum;
    uint32_t m_total_cancelnum;

    StrategyConfig()
        : m_strategy_proc("")
        , m_priority(std::numeric_limits<int>::max())
        , m_type(0)
        , m_shared_num(std::numeric_limits<int>::min())
        , m_per_val(0)
        , m_total_val(0)
        , m_rate_ordnum(0)
        , m_total_ordnum(0)
        , m_rate_cancelnum(0)
        , m_total_cancelnum(0)
    {}
};

struct TradeModeuleConfig {
    static const TradeModeuleConfig& getInstance();
    TradeModeuleConfig();
    TradeModeuleConfig(const TradeModeuleConfig&) = delete;
    TradeModeuleConfig& operator=(const TradeModeuleConfig&) = delete;

    bool Load(const char* configFileName);

    //std::vector<std::string> m_strategy_proc; //策略实例名字数组
    //std::vector<int> m_strategy_proc_types; //策略类型数组
    std::vector<StrategyConfig> m_strategy_config;  //参数数组
    uint32_t m_rtn_memqueue_len;
    uint32_t m_req_memqueue_len;
    std::string m_driver;
};

#define USE_TRADEMODULE_CFG


#endif