# Makefile
#
# Autor: Adrian Weishaupt
# erstellt am 21.10.2021
#

CC = gcc
CFLAGS = -g -W -Wall -Wextra -std=$(STD) -Wpedantic
STD = c11

TARGET = c13_3

.PHONY: all clean

all: TARGET

% : %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET).o