CC = g++
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++0x

HEADERS = $(wildcard *.hh)
SOURCES = $(patsubst %.hh, %.cc, $(HEADERS) 
OBJS = $(patsubst %.hh, %.o, $(HEADERS) )

TARGETS = regionlayer_test stock_test

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -rf $(OBJS)
	rm -rf $(TARGETS)

%.o : %.cc $(HEADER)
	$(CC) -c $(CFLAGS) -o $@ $< 

regionlayer_test : regionlayer_test.cc $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@  

stock_test : stock_test.cc $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@  
