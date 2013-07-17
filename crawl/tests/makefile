PROJECT_ROOT_DIR=/root/lxf/se
BASE_DIR=$(PROJECT_ROOT_DIR)/base
NET_DIR=$(PROJECT_ROOT_DIR)/net
CRAWL_DIR=$(PROJECT_ROOT_DIR)/crawl

COMPLIE_OPTION= -lpthread -Wall -Werror

dns:
	g++ $(BASE_DIR)/time_stamp.cc $(NET_DIR)/sock_addr.cc $(CRAWL_DIR)/dns.cc test_dns.cc -I $(PROJECT_ROOT_DIR) $(COMPLIE_OPTION) -g -o test_dns.out 

url:
	g++ $(BASE_DIR)/regex.cc $(BASE_DIR)/time_stamp.cc $(NET_DIR)/sock_addr.cc $(CRAWL_DIR)/url.cc $(CRAWL_DIR)/dns.cc test_url.cc -I $(PROJECT_ROOT_DIR) $(COMPLIE_OPTION) -g -o test_url.out

page:
	g++ $(BASE_DIR)/regex.cc $(BASE_DIR)/time_stamp.cc $(NET_DIR)/sock_addr.cc $(NET_DIR)/socket.cc $(CRAWL_DIR)/dns.cc $(CRAWL_DIR)/page.cc $(CRAWL_DIR)/url.cc $(CRAWL_DIR)/http.cc test_page.cc -I $(PROJECT_ROOT_DIR) $(COMPLIE_OPTION) -g -o test_page.out -lboost_regex

clean:
	rm *.out
