COMMON_DIR?=common
INCLUDES += -I./$(COMMON_DIR)/include
COMMON_OBJS:= \
	objs/common.o

objs/common.o: $(COMMON_DIR)/src/common.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;
