# Makefile
#
# Autor: Adrian Weishaupt
# erstellt am 10.10.2021
#

CC = gcc
CFLAGS = -g -W -Wall -Wextra -std=$(STD) -Wpedantic
STD = c11

TARGETS = \
	messung_sys \
	messung_cs

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(TARGETS).o 