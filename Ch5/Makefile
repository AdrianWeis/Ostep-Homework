# Makefile
#
# Autor: Adrian Weishaupt
# erstellt am 10.10.2021
#

CC = gcc
CFLAGS = -g -W -Wall -Wextra -std=$(STD) -Wpedantic
STD = c11

TARGETS = \
	k5_q2 \
	k5_q1 \
	k5_q3 \
	k5_q4 \
	k5_q5 \
	k5_q6 \
	k5_q7 \
	k5_q8

REMOVE = k5_q2.txt

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(TARGETS).o $(REMOVE)

