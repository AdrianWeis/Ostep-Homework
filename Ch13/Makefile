# Makefile
#
# Autor: Adrian Weishaupt
# erstellt am 21.10.2021
#

CC = gcc
CFLAGS = -g -W -Wall -Wextra -std=$(STD) -Wpedantic
STD = c11

TARGET = memory-user

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET).o