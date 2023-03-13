CXX?=g++
CXXFLAGS?=--std=c++23 -Wall

COMMON_OBJS:= objs/common.o
INCLUDES:=-I./include -I.

all: $(COMMON_OBJS)
world: $(COMMON_OBJS)

objs/common.o: src/common.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

clean:
	rm -f objs/**
