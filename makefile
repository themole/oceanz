CC = g++
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c++0x
INCLUDES = -I /usr/include/qt4/

CFLAGS += $(INCLUDES)

HEADER = $(wildcard *.hh)
SOURCES = $(patsubst %.hh, %.cc, $(HEADER) 
OBJS = $(patsubst %.hh, %.o, $(HEADER) )

THEADER = $(wildcard *.hpp)

TESTF = test
TARGETS = $(patsubst %.cc, %, $(wildcard $(TESTF)/*.cc ) )

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -rf $(OBJS)
	rm -rf $(TARGETS)

%.o : %.cc %.hh $(THEADER)
	$(CC) $(CFLAGS) -o $@ -c $< 

.SECONDEXPANSION:
$(TARGETS) : $$(addsuffix .cc, $$@ ) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $< -o $@  
