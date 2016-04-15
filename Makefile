CXXFLAGS := -std=gnu++11 -Wall -O3
CC       := $(CXX)

.PHONY: all
all: nettest

nettest: nettest.o node.o
