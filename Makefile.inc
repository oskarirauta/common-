COMMON_OBJS:= objs/common.o
INCLUDES += -I./common_cpp/include

all: $(COMMON_OBJS)
world: $(COMMON_OBJS)

objs/common.o: common_cpp/src/common.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;
