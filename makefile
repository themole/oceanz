CC = g++
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++0x 

HEADERS = $(wildcard *.hh)
SOURCES = $(patsubst %.hh, %.cc, $(HEADERS) 
OBJS = $(patsubst %.hh, %.o, $(HEADERS) )

THEADER = $(wildcard *.hpp)

TESTF = test
TARGETS = $(patsubst %.cc, %, $(wildcard $(TESTF)/*.cc ) )

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -rf $(OBJS)
	rm -rf $(TARGETS)

%.o : %.cc $(HEADER) $(THEADER)
	$(CC) $(CFLAGS) -o $@ -c $< 

.SECONDEXPANSION:
$(TARGETS) : $$(addsuffix .cc, $$@ ) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@  
