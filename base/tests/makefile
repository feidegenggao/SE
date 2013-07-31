PROJECT_ROOT_DIR=/root/lxf/se
BASE_DIR=$(PROJECT_ROOT_DIR)/base
NET_DIR=$(PROJECT_ROOT_DIR)net
COMPLIE_OPTION= -I $(PROJECT_ROOT_DIR) -Wall -Werror -lpthread -g

singleton:
	g++ test_singleton.cc $(BASE_DIR)/time_stamp.cc $(COMPLIE_OPTION) -o test_singleton.out

regex:
	g++ test_regex.cc $(BASE_DIR)/regex.cc $(BASE_DIR)/time_stamp.cc $(COMPLIE_OPTION) -lboost_regex -o test_regex.out

md5:
	g++ test_md5.cc $(BASE_DIR)/time_stamp.cc $(BASE_DIR)/md5.cc $(COMPLIE_OPTION) -lcrypto -o test_md5.out

tools:
	g++ test_tools.cc $(BASE_DIR)/time_stamp.cc $(COMPLIE_OPTION) -o test_tools.out

file:
	g++ test_file.cc $(BASE_DIR)/time_stamp.cc $(BASE_DIR)/file.cc $(COMPLIE_OPTION) -o test_file.out

clean:
	rm *.out
