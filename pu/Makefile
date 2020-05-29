CXX = g++
LINK = g++
ECHO = echo
RM = -rm -f
CP = yes|cp
MV = mv

# args
RELEASE =release
MODE =pbox 

# [args] 生成模式. 
#release: 0代表debug模式, 1代表release模式. make RELEASE=1.
ifeq ($(RELEASE), debug)
    # debug
    CXXFLAGS += -DLINUX  -std=c++11 -O3 -g -Wall
else
    # release
    CXXFLAGS += -DLINUX  -std=c++11 -O3 -DNDEBUG -Wall #-pedantic-errors
endif

#mode: 交易代理版本，pbox代表uft, 非pbox代表宽睿oes. make mode=pbox.
ifeq ($(MODE), pbox)
    # uft pbox
    CXXFLAGS += -DPBOX_TRADE_API
#else
    # quant360 oes
endif

#_CXXFLAGS= -DLINUX -Wall -g -std=c++11 #-O3 #-pedantic-errors

INC_DIR = -I.
INC_DIR += -Icommon/include
INC_DIR += -Icommon/include/jsoncpp-0.5.0
INC_DIR += -Ipublisher/include
INC_DIR += -Ipublisher/include/krmd
INC_DIR += -Ipublisher/include/krmd/mds_api
#INC_DIR += -Istock_strategy/include
#INC_DIR += -Itrademodule/include
#INC_DIR += -Itrademodule/include/kr
#INC_DIR += -Itrademodule/agw/inc
INC_DIR += -I../../cdisruptor/header
INC_DIR += -I/usr/include/mysql-cppconn-8
INC_DIR += -I../../mysql-connector-cpp8/include
INC_DIR += -I../../../stock_mon/src
INC_DIR += -I../../../../gcc484/include
INC_DIR += -I/usr/local/include/bsoncxx/v_noabi
INC_DIR += -I/usr/local/include/mongocxx/v_noabi
LIB_DIR = -L../../../../gcc484/lib -L../libs -L../libs/agw -L/usr/local/lib
SO_DIR = -Wl,-rpath=../libs -Wl,-rpath=../libs/agw

MONGO_CXX =  -ldl -lmongocxx-static -lbsoncxx-static -lmongoc-static-1.0 \
	-lbson-static-1.0  -lresolv  -lcrypto -lssl -lz -lsasl2 -loes_api

COMMON_OBJ =   common/Config.o common/datatype.o common/log.o
PUBLISHER_OBJ = publisher/wd/md_publisher.o publisher/md_main.o
KR_PUBLISHER_OBJ = publisher/krmd/md_publisher.o publisher/md_main.o
KR_MD_SAVE_OBJ = publisher/krmd/kr_md_save.o
#STRATEGY_OBJ = stock_strategy/strategy.o stock_strategy/stock_filter.o stock_strategy/trade_proxy.o stock_strategy/strategy_main.o
#TRADE_OBJ = trademodule/trade_main.o trademodule/trade_service.o trademodule/trade_risk_management.o trademodule/kr/oes_client.o trademodule/kr/oes_client_spi.o \
	    trademodule/pbox/pbox_common.o trademodule/pbox/pbox_callback.o trademodule/pbox/pbox_client.o 	
#TRADE_REPURCHASE_OBJ = trademodule/trade_repurchase.o trademodule/kr/oes_client.o stock_strategy/md_proxy.o \
		trademodule/pbox/pbox_common.o trademodule/pbox/pbox_callback.o trademodule/pbox/pbox_client.o
#CLOSE_STRATEGY_OBJ = stock_strategy/close_strategy_main.o stock_strategy/close_strategy.o stock_strategy/trade_proxy.o stock_strategy/md_proxy.o
#STOCK_STRATEGY_OBJ = stock_strategy/md_proxy.o stock_strategy/stock_strategy_common.o stock_strategy/stock_strategy_vol.o \
	stock_strategy/stock_strategy_down_sell.o stock_strategy/stock_strategy_vwap_comm.o \
	stock_strategy/stock_strategy_vwap_b.o stock_strategy/stock_strategy_vwap_c_buy.o \
	stock_strategy/stock_strategy_vwap_s.o  stock_strategy/stock_strategy_vwap.o \
	stock_strategy/stock_strategy.o stock_strategy/stock_strategy_main.o stock_strategy/trade_proxy.o

CXX_OBJS = $(COMMON_OBJ)
#CXX_OBJS += $(PUBLISHER_OBJ)
CXX_OBJS += $(KR_PUBLISHER_OBJ)
CXX_OBJS += $(KR_MD_SAVE_OBJ)
#CXX_OBJS += $(STRATEGY_OBJ)
#CXX_OBJS += $(TRADE_REPURCHASE_OBJ)
#CXX_OBJS += $(TRADE_OBJ)
#CXX_OBJS += $(CLOSE_STRATEGY_OBJ)
#CXX_OBJS += $(STOCK_STRATEGY_OBJ)

#BIN_DIR = ../bin
#PUBLISHER = $(BIN_DIR)/stock_publisher
#KR_PUBLISHER = $(BIN_DIR)/kr_stock_publisher
#STRATEGY = $(BIN_DIR)/strategy_proc
#TRADEMODULE = $(BIN_DIR)/trademodule
#ifeq ($(MODE), pbox)
#    # uft pbox
#    DEST_TRADEMODULE = $(BIN_DIR)/pbox_trademodule
#else
#    # quant360 oes
#	DEST_TRADEMODULE = $(BIN_DIR)/oes_trademodule
#endif
KR_MD_SAVE = ./publisher/krmd/kr_md_save
#TRADE_REPURCHASE = $(BIN_DIR)/trade_repurchase
#CLOSE_STRATEGY = $(BIN_DIR)/close_strategy_proc
#STOCK_STRATEGY = $(BIN_DIR)/twap_proc

.PHONY: clean all after_build

#all: $(TRADEMODULE) ${STOCK_STRATEGY} $(KR_PUBLISHER)  $(KR_MD_SAVE) $(TRADE_REPURCHASE)
#all: $(PUBLISHER) $(KR_PUBLISHER) $(TRADEMODULE) $(KR_MD_SAVE) $(TRADEMODULE)  ${CLOSE_STRATEGY} after_build
all:    $(PUBLISHER) $(KR_PUBLISHER)  $(KR_MD_SAVE)



$(CXX_OBJS):%.o:%.cpp
	@$(ECHO) "begin compile source:" $@
	$(CXX) $(INC_DIR) -c $^  $(CXXFLAGS) -o $@
	@$(ECHO) "end compiling source:" $@

$(PUBLISHER):$(PUBLISHER_OBJ) $(COMMON_OBJ)
	@$(ECHO) "begin linking library:" $@
	$(LINK) $^ $(LIB_DIR) $(SO_DIR) -lpthread -lm -lcdisruptor -lrt -lTDFAPI_v2.5 -lWHNetWork ${MONGO_CXX} -o $@
	@$(ECHO) "end linking library:" $@
	
$(KR_PUBLISHER):$(KR_PUBLISHER_OBJ) $(COMMON_OBJ)
	@$(ECHO) "begin linking library:" $@
	$(LINK) $^ $(LIB_DIR) $(SO_DIR) -ljson_linux-gcc-4.8.5_libmt -lpthread -lm -lcdisruptor -llog4cplus -lrt \
	-loes_api ${MONGO_CXX} -o $@
	@$(ECHO) "end linking library:" $@
	
$(KR_MD_SAVE):$(KR_MD_SAVE_OBJ) $(COMMON_OBJ)
	@$(ECHO) "begin linking library:" $@
	$(LINK) $^ $(LIB_DIR) $(SO_DIR) -ljson_linux-gcc-4.8.5_libmt -lpthread -lm  -llog4cplus  -lrt \
	${MONGO_CXX} -o $@
	@$(ECHO) "end linking library:" $@

#$(STRATEGY):$(STRATEGY_OBJ) $(COMMON_OBJ)
#	@$(ECHO) "begin linking library:" $@
#	$(LINK) $^ $(LIB_DIR) $(SO_DIR) -lpthread -lm -lcdisruptor  -lmysqlcppconn8 -lcrypto -lssl -lrt ${MONGO_CXX} -o $@
#	@$(ECHO) "end linking library:" $@
#
#$(TRADEMODULE):$(TRADE_OBJ) $(COMMON_OBJ)
#	@$(ECHO) "begin linking library:" $@
#	$(LINK) $^ $(LIB_DIR) $(SO_DIR) -Bstatic -lpthread -lm -lcdisruptor -llog4cplus -lrt -loes_api -lt2sdk \
#	-ljson_linux-gcc-4.8.5_libmt ${MONGO_CXX} -o $@
#	$(CP) $(TRADEMODULE) $(DEST_TRADEMODULE)
#	@$(ECHO) "end linking library:" $@
#
#$(TRADE_REPURCHASE):$(TRADE_REPURCHASE_OBJ) $(COMMON_OBJ)
#	@$(ECHO) "begin linking library:" $@
#	$(LINK) $^ $(LIB_DIR) $(SO_DIR) -lpthread -lm -lcdisruptor -llog4cplus -lrt -loes_api -lt2sdk \
#	-ljson_linux-gcc-4.8.5_libmt ${MONGO_CXX} -o $@
#	@$(ECHO) "end linking library:" $@
#
#$(CLOSE_STRATEGY):$(CLOSE_STRATEGY_OBJ) $(COMMON_OBJ)
#	@$(ECHO) "begin linking library:" $@
#	$(LINK) $^ $(LIB_DIR) $(SO_DIR) -lpthread -lm -lcdisruptor -lrt ${MONGO_CXX} -o $@
#	@$(ECHO) "end linking library:" $@
#
#$(STOCK_STRATEGY):$(STOCK_STRATEGY_OBJ) $(COMMON_OBJ)
#	@$(ECHO) "begin linking library:" $@
#	$(LINK) $^ $(LIB_DIR) $(SO_DIR)  -lpthread -lm -lcdisruptor -llog4cplus -ltrade_agent -lrt ${MONGO_CXX} -l:libzmq.a -o $@
#	@$(ECHO) "end linking library:" $@

clean:
	$(RM) $(CXX_OBJS) $(TRADEMODULE) ${STOCK_STRATEGY} $(KR_PUBLISHER)  $(KR_MD_SAVE) $(TRADE_REPURCHASE)

after_build:
	$(CP) config.cfg ./trademodule/kr/oes_client.conf ./publisher/krmd/mds_client.conf ../bin
