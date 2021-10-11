#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    struct timespec loopStart,loopEnd,clockStart,clockEnd;
    int iterations = 10000000; //10^9 war zu viel...

    clock_gettime(CLOCK_MONOTONIC_RAW,&loopStart);
    for(int i = 0; i < iterations; i++)
    {
        
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&loopEnd);

    long double avrLoopTime = ((long double) loopStart.tv_nsec - (long double) loopEnd.tv_nsec)/(double) iterations;
    
    clock_gettime(CLOCK_MONOTONIC_RAW,&clockStart);
    for(int i = 0; i < iterations; i++)
    {
        read(0,NULL,0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&clockEnd);

    long double avrRead = ((long double) clockStart.tv_nsec - (long double) clockEnd.tv_nsec)/(long double) iterations;
    printf("Durchschnittliche Dauer einer Schleife in: %Lf nsec\n", avrLoopTime);
    printf("Durchschnittliche Dauer eines 0ByteReads in: %Lf nsec\n", avrRead);

    return 0;
}