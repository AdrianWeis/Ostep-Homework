# Makefile
#
# Autor: Adrian Weishaupt
# erstellt am 26.10.2021
#

CC = gcc
CFLAGS = -g -W -Wall -Wextra -std=$(STD) -Wpedantic
STD = c11

TARGET = \
	null \
	array \
	node

% : %.o
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET).o $(TARGET)

node.o: node.c node.h