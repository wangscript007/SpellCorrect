src = $(wildcard *.cc, ./lib_json/*.cpp)
targets = main

CC = g++
CFLAGS = -g -Wall 

all:$(targets)

$(targets):%:%.cc
	$(CC) $< -o $@ $(CFLAGS)

.PHONY:clean all
clean:
	-rm -rf $(targets) 
