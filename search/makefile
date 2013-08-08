PROJECT_ROOT=..
BASE_DIR=$(PROJECT_ROOT)/base
NET_DIR=$(PROJECT_ROOT)/net
INDEX_MATCH_DIR=$(PROJECT_ROOT)/index_match
COMPLIE_OPTION= -g -Wall -Werror -I$(PROJECT_ROOT) 
COMPLIE_LIB= -lpthread 

all:
	g++ main.cc search.cc doc_index.cc inverted_index.cc forward_index_index.cc $(INDEX_MATCH_DIR)/inverted_map.cc $(INDEX_MATCH_DIR)/participle.cc $(INDEX_MATCH_DIR)/dict.cc $(INDEX_MATCH_DIR)/doc_raw.cc $(BASE_DIR)/file.cc $(BASE_DIR)/time_stamp.cc $(BASE_DIR)/regex.cc $(NET_DIR)/socket.cc $(NET_DIR)/sock_addr.cc $(COMPLIE_OPTION) $(COMPLIE_LIB) -lboost_regex -o search.out

clean:
	rm *.out

indexclean:
	rm *.index
