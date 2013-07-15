PROJECT_ROOT_DIR=/root/lxf/se
BASE_COMPLIE_FILES=$(PROJECT_ROOT_DIR)/base/time_stamp.cc
COMPLIE_OPTION= -lpthread -Wall -Werror

dns:
	g++ $(PROJECT_ROOT_DIR)/crawl/dns.cc test_dns.cc $(BASE_COMPLIE_FILES) -g -o test_dns.out -I $(PROJECT_ROOT_DIR) $(COMPLIE_OPTION)

clean:
	rm *.out
