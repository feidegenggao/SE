PROJECT_ROOT_DIR=../../
BASE_DIR=$(PROJECT_ROOT_DIR)/base
NET_DIR=$(PROJECT_ROOT_DIR)/net
COMPLIE_OPTION= -Wall -Werror
LIBS= -lpthread 

sock_addr:
	g++ test_sock_addr.cc	$(PROJECT_ROOT_DIR)/net/sock_addr.cc $(PROJECT_ROOT_DIR)/base/time_stamp.cc -I $(PROJECT_ROOT_DIR) -g -o test_sock_addr.out $(COMPLIE_OPTION)

socket:
	g++ test_socket.cc $(BASE_DIR)/time_stamp.cc $(NET_DIR)/socket.cc $(NET_DIR)/sock_addr.cc -I $(PROJECT_ROOT_DIR) $(COMPLIE_OPTION) $(LIBS) -g -o test_socket.out
