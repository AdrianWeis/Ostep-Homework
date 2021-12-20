# Makefile
#
# Autor: Adrian Weishaupt
# erstellt am 20.12.2021
#

CC = gcc
STD = c11
CFLAGS = -g -W -Wall -Wextra -std=$(STD) -Wpedantic -pthread


all: c29_2

clean:
	rm -f c29_2

c29_2: c29_2.c
	$(CC) -o c29_2 c29_2.c $(CFLAGS)