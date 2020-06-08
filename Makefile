CXX = g++
LINK = g++
ECHO = echo
RM = -rm -f
CP = yes|cp
MV = mv

# args
RELEASE =release
MODE =pbox 

# [args] 鐢熸垚妯″紡. 
#release: 0浠ｈ〃debug妯″紡, 1浠ｈ〃release妯″紡. make RELEASE=1.
ifeq ($(RELEASE), debug)
    # debug
    CXXFLAGS += -DLINUX  -std=c++11 -O3 -g -Wall
else
    # release
    CXXFLAGS += -DLINUX  -std=c++11 -O3 -DNDEBUG -Wall #-pedantic-errors
endif

#mode: 浜ゆ槗浠ｇ悊鐗堟湰锛宲box浠ｈ〃uft, 闈瀙box浠ｈ〃瀹界澘oes. make mode=pbox.
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
# INC_DIR += -Ipublisher/include/krmd/
# INC_DIR += -Ipublisher/include/krmd/mds_api
INC_DIR += -Icdisruptor/header
INC_DIR += -I/usr/local/include/bsoncxx/v_noabi
INC_DIR += -I/usr/local/include/mongocxx/v_noabi
LIB_DIR =  -L/usr/local/lib #-L../../../../gcc484/lib -L../libs -L../libs/agw
INC_DIR += -Ipublisher/include/h5md
INC_DIR += -Ipublisher/include/h5md/h5sdk
INC_DIR += -Ipublisher/h5md
INC_DIR += -Ipublisher/h5md/MyUtil

# outside link library
MONGO_CXX =  -ldl -lmongocxx-static -lbsoncxx-static -lmongoc-static-1.0 \
	-lbson-static-1.0  -lresolv  -lcrypto -lssl -lz -lsasl2 -loes_api \
	-lf_os -lfsc_f2config -lfsc_hscommsg -lh5sdk -lhs_best_message

# generate objects
COMMON_OBJ =   common/Config.o common/datatype.o common/log.o
# PUBLISHER_OBJ = publisher/wd/md_publisher.o publisher/md_main.o
#KR_PUBLISHER_OBJ = publisher/krmd/md_publisher3.o publisher/md_main.o
KR_PUBLISHER_OBJ = publisher/h5md/h5md_publisher.o publisher/h5md/main_environment.o  \
				   publisher/h5md/main_message_queue.o publisher/h5md/sdk_callback.o  publisher/h5md/sdk_data_parser.o\
				   publisher/h5md/sdk_configure.o publisher/h5md/sdk_util.o publisher/h5md/sdk_capability.o \
				   publisher/h5md/MyAutoLock.o publisher/h5md/MyEvent.o publisher/h5md/MyThread.o \
				   publisher/md_main.o 
		

#KR_MD_SAVE_OBJ = publisher/krmd/kr_md_save.o

CXX_OBJS = $(COMMON_OBJ)
CXX_OBJS += $(KR_PUBLISHER_OBJ)
#CXX_OBJS += $(KR_MD_SAVE_OBJ)

KR_PUBLISHER = ./publisher/h5md/demo

.PHONY: clean all after_build

all:    $(PUBLISHER) $(KR_PUBLISHER) #$(KR_MD_SAVE)

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
