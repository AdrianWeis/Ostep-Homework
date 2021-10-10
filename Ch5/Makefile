# Makefile
#
# Autor: Adrian Weishaupt
# erstellt am 10.10.2021
#

CC = gcc
CFLAGS = -g -W -Wall -std=$(STD) -pedantic
CPPCHECK = cppcheck --enable=warning,style --std=$(STD)
STD = c11

TARGETS = \
	k5_q2.c \
	k5_q1.c 

$(TARGETS): $(TARGETS:.c=.o)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: all clean cppcheck

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(TARGETS:.c=.o)

cppcheck: $(TARGETS)
	$(CPPCHECK) $^
