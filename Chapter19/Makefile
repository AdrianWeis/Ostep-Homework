# Makefile
# Author: Simon Kaemmer + Adrian

# Variablen
CC = gcc
CFLAGS = -g -W -Wall -Wextra -std=$(STD) -Wpedantic
STD = c11

TARGET = tlb

% : %.o
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET).o $(TARGET)

tlb.o: tlb.c tlb.h
