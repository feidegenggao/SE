include ../path.mk
LOAD_LIB= -lpthread -lcrypto -lboost_regex 

all:
	g++ main.cc dict.cc index.cc doc_raw.cc inverted_map.cc participle.cc $(BASE_DIR)/time_stamp.cc $(BASE_DIR)/md5.cc $(BASE_DIR)/regex.cc $(COMPLIE_OPTION) $(LOAD_LIB) -I $(PROJECT_ROOT_DIR) -I $(LIB_DIR) -o index.out

clean:
	rm *.out
	rm *.index

outclean:
	rm *.out

indexclean:
	rm *.index
