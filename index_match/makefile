PROJECT_ROOT=../
BASE_DIR=$(PROJECT_ROOT)/base
NET_DIR=$(PROJECT_ROOT)/net
COMPLIE_OPTION= -g -Wall -Werror -I$(PROJECT_ROOT) 
COMPLIE_LIB= -lpthread -lcrypto -lboost_regex 

all:
	g++ main.cc dict.cc index.cc doc_raw.cc inverted_map.cc participle.cc $(BASE_DIR)/time_stamp.cc $(BASE_DIR)/md5.cc $(BASE_DIR)/regex.cc $(COMPLIE_OPTION) $(COMPLIE_LIB) -o index.out

clean:
	rm *.out
	rm *.index

outclean:
	rm *.out

indexclean:
	rm *.index
