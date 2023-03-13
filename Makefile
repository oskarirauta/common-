CXX?=g++
CXXFLAGS?=--std=c++23

COMMON_CPP_OBJS:= objs/common.o
INCLUDES:=-I./include -I.

all: $(COMMON_CPP_OBJS)
world: $(COMMON_CPP_OBJS)

objs/common.o: src/common.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

clean:
	rm -f objs/**
