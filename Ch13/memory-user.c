#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char*argv[])
{
    if (argc != 3){
        printf("Fehlerhafteraufruf: memory-user byteAnzahl DauerSec\n");
        return -1;
    }

    int bAnz;
    int secAnz;
    int mbTob = 1048576;
    char *p;
    struct timespec loopEnd, now;

    errno = 0;
    long conv = strtol(argv[1], &p, 10);

    if (errno != 0 || *p != '\0' || conv > INT_MAX || conv < INT_MIN) {
        fprintf(stderr,"Second Argument needs to be a Int\n");
        return -1;
    } else {
        bAnz = conv*(mbTob/sizeof(int));
    }

    conv = strtol(argv[2], &p, 10);

    if (errno != 0 || *p != '\0' || conv > INT_MAX || conv < INT_MIN) {
        fprintf(stderr,"Third Argument needs to be a Int\n");
        return -1;
    } else {
        secAnz = conv;
    }

    printf("Anzahl anzulegender Integer:%d\n", bAnz);

    int* array = calloc(bAnz,sizeof(int));
    assert(array);
    
    printf("Realisierte Arraysize: %ld\n", sizeof(array));
    printf("Programm ID von memory-user:%d\n", getpid());

    clock_gettime(CLOCK_MONOTONIC_RAW,&loopEnd);

    while (1)
    {
        for (int i = 0; i <= bAnz; i++)
        {
            array[i];
            if(i%10 == 0)
            {
                clock_gettime(CLOCK_MONOTONIC_RAW,&now);
                if (now.tv_sec >= loopEnd.tv_sec + secAnz)
                {
                    free(array);
                    return 1;
                }
            }
        }
    }
}