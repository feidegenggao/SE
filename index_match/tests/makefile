PROJECT_ROOT=/root/lxf/se
BASE_DIR=$(PROJECT_ROOT)/base
NET_DIR=$(PROJECT_ROOT)/net
COMPLIE_OPTION= -g -Wall -Werror -I$(PROJECT_ROOT) 
COMPLIE_LIB= -lpthread 

dict:
	g++ test_dict.cc $(PROJECT_ROOT)/index_match/dict.cc $(BASE_DIR)/time_stamp.cc $(COMPLIE_OPTION) $(COMPLIE_LIB) -o test_dict.out

clean:
	rm *.out
