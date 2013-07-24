PROJECT_ROOT=/root/lxf/se
BASE_DIR=$(PROJECT_ROOT)/base
NET_DIR=$(PROJECT_ROOT)/net
INDEX_MATCH_DIR=$(PROJECT_ROOT)/index_match
COMPLIE_OPTION= -g -Wall -Werror -I$(PROJECT_ROOT) 
COMPLIE_LIB= -lpthread 

all:
	g++ main.cc inverted_index.cc $(INDEX_MATCH_DIR)/inverted_map.cc $(BASE_DIR)/time_stamp.cc $(COMPLIE_OPTION) $(COMPLIE_LIB) -o search.out

outclean:
	rm *.out

indexclean:
	rm *.index
