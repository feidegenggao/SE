PROJECT_ROOT_DIR=/root/lxf/se
BASE_COMPLIE_FILES=$(PROJECT_ROOT_DIR)/base/time_stamp.cc
COMPLIE_OPTION= -Wall -Werror -lpthread

singleton:
	g++ test_singleton.cc $(BASE_COMPLIE_FILES) -g -o test_singleton.out -I $(PROJECT_ROOT_DIR) $(COMPLIE_OPTION)

regex:
	g++ test_regex.cc $(PROJECT_ROOT_DIR)/base/regex.cc $(BASE_COMPLIE_FILES) -g -o test_regex.out -I $(PROJECT_ROOT_DIR) $(COMPLIE_OPTION)

clean:
	rm *.out
