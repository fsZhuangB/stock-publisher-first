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

# include directories
INC_DIR = -I.
INC_DIR += -Icommon/include
INC_DIR += -Ipublisher/include
INC_DIR += -Ipublisher/include/krmd/
INC_DIR += -Ipublisher/include/krmd/mds_api
INC_DIR += -Icdisruptor/header
INC_DIR += -I/usr/local/include/bsoncxx/v_noabi
INC_DIR += -I/usr/local/include/mongocxx/v_noabi
LIB_DIR =  -L/usr/local/lib #-L../../../../gcc484/lib -L../libs -L../libs/agw

# outside link library
MONGO_CXX =  -ldl -lmongocxx-static -lbsoncxx-static -lmongoc-static-1.0 \
	-lbson-static-1.0  -lresolv  -lcrypto -lssl -lz -lsasl2 -loes_api

# generate objects
COMMON_OBJ =   common/Config.o common/datatype.o common/log.o
# PUBLISHER_OBJ = publisher/wd/md_publisher.o publisher/md_main.o
KR_PUBLISHER_OBJ = publisher/krmd/md_publisher3.o publisher/md_main.o
#KR_MD_SAVE_OBJ = publisher/krmd/kr_md_save.o

CXX_OBJS = $(COMMON_OBJ)
CXX_OBJS += $(KR_PUBLISHER_OBJ)
#CXX_OBJS += $(KR_MD_SAVE_OBJ)

KR_PUBLISHER = ./publisher/krmd/demo

.PHONY: clean all after_build

all:    $(PUBLISHER) $(KR_PUBLISHER)  #$(KR_MD_SAVE)

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
	
# $(KR_MD_SAVE):$(KR_MD_SAVE_OBJ) $(COMMON_OBJ)
# 	@$(ECHO) "begin linking library:" $@
# 	$(LINK) $^ $(LIB_DIR) $(SO_DIR) -ljson_linux-gcc-4.8.5_libmt -lpthread -lm  -llog4cplus  -lrt \
# 	${MONGO_CXX} -o $@
# 	@$(ECHO) "end linking library:" $@

clean:
	$(RM) $(CXX_OBJS) $(TRADEMODULE) ${STOCK_STRATEGY} $(KR_PUBLISHER)   

after_build:
	$(CP) config.cfg ./trademodule/kr/oes_client.conf ./publisher/krmd/mds_client.conf ../bin
