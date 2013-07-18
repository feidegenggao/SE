PROJECT_ROOT_DIR=/root/lxf/se
BASE_DIR=$(PROJECT_ROOT_DIR)/base
NET_DIR=$(PROJECT_ROOT_DIR)/net

COMPILE_OPTION= -g -Wall -Werror -lpthread -lboost_regex 

all:
	g++ main.cc dns.cc http.cc url.cc page.cc $(BASE_DIR)/regex.cc $(BASE_DIR)/time_stamp.cc $(NET_DIR)/sock_addr.cc $(NET_DIR)/socket.cc -I $(PROJECT_ROOT_DIR) $(COMPILE_OPTION) -o crawl.out 

clean:
	rm crawl.out

rawclean:
	rm *.raw
