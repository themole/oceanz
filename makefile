CC = g++

CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++0x
DEBUGFLAGS = -ggdb

CFLAGS += $(INCLUDES)

HEADER = $(wildcard *.hh)
SOURCES = $(patsubst %.hh, %.cc, $(HEADER) 
OBJS = $(patsubst %.hh, %.o, $(HEADER) )

THEADER = $(wildcard *.hpp)

TESTF = test
TARGETS = $(patsubst %.cc, %, $(wildcard $(TESTF)/*.cc ) )

.PHONY: all debug clean

all: $(TARGETS)

debug: CFLAGS+=$(DEBUGFLAGS)
debug: all

clean:
	rm -rf $(OBJS)
	rm -rf $(TARGETS)

%.o : %.cc %.hh $(THEADER)
	$(CC) $(CFLAGS) -o $@ -c $< 

.SECONDEXPANSION:
$(TARGETS) : $$(addsuffix .cc, $$@ ) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@  
