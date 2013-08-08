include ../path.mk

LOAD_LIB= -lpthread -lboost_regex 

all:
	g++ main.cc dns.cc http.cc url.cc page.cc $(BASE_DIR)/regex.cc $(BASE_DIR)/time_stamp.cc $(NET_DIR)/sock_addr.cc $(NET_DIR)/socket.cc -I $(PROJECT_ROOT_DIR) -I $(LIB_DIR) $(COMPILE_OPTION) $(LOAD_LIB) -o crawl.out 

clean:
	rm crawl.out

rawclean:
	rm *.raw
