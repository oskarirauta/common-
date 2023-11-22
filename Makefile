all: world
CXX?=g++
CXXFLAGS?=--std=c++23 -Wall -fPIC -g
LDFLAGS?=-L/lib -L/usr/lib

INCLUDES+= -I./include

OBJS:= \
	objs/test.o

COMMON_DIR:=.
include ./Makefile.inc

world: test

objs/test.o: test.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;

test: $(COMMON_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -L. $(LIBS) $^ -o $@;

.PHONY: clean
clean:
	rm -f objs/*.o test
