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
	k5_q2 \
	k5_q1 \

.PHONY: all clean cppcheck

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(TARGETS).o

$(TARGETS): $(TARGETS).o
	$(CC) $(CFLAGS) -o $@ $^

cppcheck: $(TARGETS).c
	$(CPPCHECK) $^