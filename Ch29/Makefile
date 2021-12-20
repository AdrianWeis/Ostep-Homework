# Makefile
#
# Autor: Adrian Weishaupt
# erstellt am 20.12.2021
#

CC = gcc
STD = c11
CFLAGS = -g -W -Wall -Wextra -std=$(STD) -Wpedantic -pthread


all: c29_2 c29_3 test

clean:
	rm -f c29_2 c29_3

c29_2: c29_2.c c29.h
	$(CC) -o c29_2 c29_2.c $(CFLAGS)

c29_3: c29_3.c c29.h
	$(CC) -o c29_3 c29_3.c $(CFLAGS)

test: test.c c29.h
	$(CC) -o test test.c $(CFLAGS)