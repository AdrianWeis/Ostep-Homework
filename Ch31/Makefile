# Makefile
#
# Autor: Adrian Weishaupt
# erstellt am 09.01.2022
#

CC = gcc
STD = c11
CFLAGS = -g -W -Wall -Wextra -std=$(STD) -Wpedantic -pthread
TARGETS = fork-join \
	rendezvous \
	barrier \
	reader-writer

% : %.o
	$(CC) $(CFLAGS) -o $@ $<

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(TARGETS).o

fork-join.o: fork-join.c common_threads.h

rendezvous.o: rendezvous.c common_threads.h

barrier.o: barrier.c common_threads.h

reader-writer.o: reader-writer.c common_threads.h