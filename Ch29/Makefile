# Makefile
#
# Autor: Adrian Weishaupt
# erstellt am 20.12.2021
#

CC = gcc
STD = c11
CFLAGS = -g -W -Wall -Wextra -std=$(STD) -Wpedantic -pthread


all: c29_2 c29_3 c29_4 hoh test

clean:
	rm -f c29_2 c29_3 c29_4 hoh test

c29_2: c29_2.c c29.h
	$(CC) -o c29_2 c29_2.c $(CFLAGS)

c29_3: c29_3.c c29.h
	$(CC) -o c29_3 c29_3.c $(CFLAGS)

c29_4: c29_4.c c29.h
	$(CC) -o c29_4 c29_4.c $(CFLAGS)

hoh: hoh.c c29.h
	$(CC) -o hoh hoh.c $(CFLAGS)

test: test.c c29.h
	$(CC) -o test test.c $(CFLAGS)