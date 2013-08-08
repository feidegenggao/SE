include ../path.mk

INDEX_MATCH_DIR=$(PROJECT_ROOT_DIR)/index_match
LOAD_LIB= -lpthread -lboost_regex 

all:
	g++ main.cc search.cc doc_index.cc inverted_index.cc forward_index_index.cc $(INDEX_MATCH_DIR)/inverted_map.cc $(INDEX_MATCH_DIR)/participle.cc $(INDEX_MATCH_DIR)/dict.cc $(INDEX_MATCH_DIR)/doc_raw.cc $(BASE_DIR)/file.cc $(BASE_DIR)/time_stamp.cc $(BASE_DIR)/regex.cc $(NET_DIR)/socket.cc $(NET_DIR)/sock_addr.cc $(COMPLIE_OPTION) $(LOAD_LIB) -I $(PROJECT_ROOT_DIR) -I $(LIB_DIR) -o search.out

clean:
	rm *.out

indexclean:
	rm *.index
