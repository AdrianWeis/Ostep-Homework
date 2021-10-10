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
	k5_q1 

$(TARGETS): $(TARGETS).o
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: all clean cppcheck

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(TARGETS).o

cppcheck: $(TARGETS).c
	$(CPPCHECK) $^

k5_q1.o: k5_q1.c
k5_q2.o: k5_q2.c 