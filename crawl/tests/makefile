include ../../path.mk
CRAWL_DIR=$(PROJECT_ROOT_DIR)/crawl

LOAD_LIB=-lpthread

dns:
	g++ $(BASE_DIR)/time_stamp.cc $(NET_DIR)/sock_addr.cc $(CRAWL_DIR)/dns.cc test_dns.cc  $(COMPLIE_OPTION) $(LOAD_LIB) -I $(LIB_DIR) -I $(PROJECT_ROOT_DIR) -o test_dns.out 

url:
	g++ $(BASE_DIR)/regex.cc $(BASE_DIR)/time_stamp.cc $(NET_DIR)/sock_addr.cc $(CRAWL_DIR)/url.cc $(CRAWL_DIR)/dns.cc test_url.cc $(COMPLIE_OPTION) $(LOAD_LIB) -I $(LIB_DIR) -I $(PROJECT_ROOT_DIR) -o test_url.out -lboost_regex

page:
	g++ $(BASE_DIR)/regex.cc $(BASE_DIR)/time_stamp.cc $(NET_DIR)/sock_addr.cc $(NET_DIR)/socket.cc $(CRAWL_DIR)/dns.cc $(CRAWL_DIR)/page.cc $(CRAWL_DIR)/url.cc $(CRAWL_DIR)/http.cc test_page.cc $(COMPLIE_OPTION) $(LOAD_LIB) -I $(LIB_DIR) -I $(PROJECT_ROOT_DIR) -o test_page.out -lboost_regex

http:
	g++ test_http.cc $(CRAWL_DIR)/http.cc $(CRAWL_DIR)/dns.cc $(CRAWL_DIR)/url.cc $(BASE_DIR)/time_stamp.cc $(NET_DIR)/socket.cc $(BASE_DIR)/regex.cc $(COMPLIE_OPTION) $(LOAD_LIB) -I $(LIB_DIR) -I $(PROJECT_ROOT_DIR) -lboost_regex -o test_http.out

clean:
	rm *.out
