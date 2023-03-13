COMMON_DIR?=common
COMMON_OBJS:= objs/common.o
INCLUDES += -I./$(COMMON_DIR)/include

all: $(COMMON_OBJS)
world: $(COMMON_OBJS)

objs/common.o: $(COMMON_DIR)/src/common.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;
