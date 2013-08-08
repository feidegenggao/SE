include ../../path.mk

LOAD_LIB= -lpthread 

dict:
	g++ test_dict.cc $(PROJECT_ROOT_DIR)/index_match/dict.cc $(BASE_DIR)/time_stamp.cc $(COMPLIE_OPTION) $(LOAD_LIB) -I $(PROJECT_ROOT_DIR) -I $(LIB_DIR) -o test_dict.out

inverted_map:
	g++ test_inverted_map.cc ../inverted_map.cc $(BASE_DIR)/time_stamp.cc $(COMPLIE_OPTION) $(LOAD_LIB) -I $(PROJECT_ROOT_DIR) -I $(LIB_DIR) -o test_inverted_map.out

lean:
	rm *.out
