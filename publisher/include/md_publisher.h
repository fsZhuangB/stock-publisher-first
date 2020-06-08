#ifndef MD_PUBLISHER_H
#define MD_PUBLISHER_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include <sys/stat.h>
#include <dirent.h>
#include "csv.h"
#include "Config.h"
#include "datatype.h"

void start_md(Config& config);

static vector<PVO> read_stock_order(vector<string> paths)
{
    vector<PVO> orders;
    for (auto const& fullpath : paths)
    {
        fprintf(stdout, "%s\n", fullpath.c_str());
        try {
            io::CSVReader<8> in(fullpath);
            in.read_header(io::ignore_extra_column, "systime","szCode","nTime","nOrder","nPrice", "nVolume", "chOrderKind", "chFunctionCode");
            string szCode;
            int nTime,nOrder,nPrice,nVolume;
            char chOrderKind,chFunctionCode;
            unsigned long systime;
            while(in.read_row(systime,szCode,nTime,nOrder,nPrice,nVolume,chOrderKind,chFunctionCode)){
                if (chOrderKind == '1' || chOrderKind == 'U') {//市价或本方最优价
                    nPrice = INT_MAX;
                }
                PVO pvo;
                pvo.instrId = std::stoi(szCode);
                strncpy(pvo.code, szCode.c_str(), szCode.size()+1);
                pvo.seq_num = nOrder;
                pvo.price = nPrice;
                pvo.vol = nVolume;
                pvo.recv_nano = systime;
                pvo.type = TYPE_ORDER;
                pvo.update_time = nTime;
                if(chFunctionCode == 'B') {
                    pvo.direction = DIRECTION_BUY;
                } else if(chFunctionCode == 'S') {
                    pvo.direction = DIRECTION_SELL;
                }
                orders.push_back(pvo);
            }
        } catch (...) {
            //printf("%s\n", e.what());
        }
    }
    return orders;
}

static vector<PVO> read_stock_trade(vector<string> paths)
{
    vector<PVO> trades;
    for (auto const& fullpath : paths)
    {
        fprintf(stdout, "%s\n", fullpath.c_str());
        try {
            io::CSVReader<5> in(fullpath);
            in.read_header(io::ignore_extra_column,"systime", "szCode","nAskOrder","nBidOrder","nVolume");
            int szCode,nAskOrder,nBidOrder,nVolume;
            unsigned long systime;
            unsigned long pre_systime = 0;
        
            while(in.read_row(systime,szCode,nAskOrder,nBidOrder,nVolume)){
                
                if  (nBidOrder == 0) {//卖撤单
                    continue;
                }
                PVO pvo;
                pvo.instrId = szCode;
                pvo.seq_num = nBidOrder;
                pvo.vol = nVolume;
                if  (nAskOrder == 0) {//买撤单
                    pvo.vol = INT_MAX;
                }
                if (pre_systime == systime && nAskOrder == 0) {
                    pvo.recv_nano = systime + 1;
                } else {
                    pvo.recv_nano = systime;
                }
                
                pvo.type = TYPE_TRADE;
                trades.push_back(pvo);
                pre_systime = systime;//为了解决时间相同的订单，撤单先排在前面的问题
            }
        } catch (...) {
            //printf("%s\n", e.what());
        }
    }
    return trades;
}

static vector<PVO> read_stock_snapshot(vector<string> paths)
{
    vector<PVO> snapshots;
    for (auto const& fullpath : paths)
    {
        fprintf(stdout, "%s\n", fullpath.c_str());
        try {
            io::CSVReader<11> in(fullpath);
            in.read_header(io::ignore_extra_column, "systime","szCode","nTime","nOpen","nPreClose", "iVolume","bp1", "bv1","bp2","ap1","av1");
            string szCode;
            int nTime,nOpen,nPreClose,nVolume,bp1,bv1,bp2,ap1,av1;

            unsigned long systime;
        
            while(in.read_row(systime,szCode,nTime,nOpen,nPreClose,nVolume,bp1, bv1,bp2,ap1,av1)){
                PVO data;
                data.recv_nano =  systime;
                data.instrId = std::stoi(szCode);
                strncpy(data.code, szCode.c_str(), szCode.size() + 1);
                data.price = nOpen;
                data.pre_close = nPreClose;
                data.update_time = nTime;
                data.vol = nVolume;
                data.bid_prices[0] = bp1;
                data.bid_vols[0] = bv1;
                data.bid_prices[1] = bp2;
                data.ask_prices[0] = ap1;
                data.ask_vols[0] = av1;
                data.type = TYPE_SNAPSHOT;
                snapshots.push_back(data);
            }
        } catch (...) {
            //printf("%s\n", e.what());
        }
    }
    return snapshots;
}
static bool less_sort (PVO a,PVO b) { return (a.recv_nano < b.recv_nano); } 
#endif /* MD_PUBLISHER_H */
