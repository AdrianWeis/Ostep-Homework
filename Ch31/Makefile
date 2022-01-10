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
	reader-writer \
	reader-writer-no-starve \
	rw-noStarve-block \
	rw-no-starve \
	mutex-nostarve

% : %.o
	$(CC) $(CFLAGS) -o $@ $<

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(TARGETS).o

fork-join.o: fork-join.c common_threads.h

rendezvous.o: rendezvous.c common_threads.h

barrier.o: barrier.c common_threads.h

reader-writer.o: reader-writer.c common_threads.h

reader-writer-no-starve.o: reader-writer-no-starve.c common_threads.h

rw-noStarve-block.o: rw-noStarve-block.c common_threads.h

rw-no-starve.o: rw-no-starve.c common_threads.h

mutex-nostarve.o: mutex-nostarve.c common_threads.h