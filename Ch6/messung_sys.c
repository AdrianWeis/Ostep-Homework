#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    struct timespec loopStart,loopEnd,clockStart,clockEnd, clockErrS,clockErrE;
    int iterations = 20000000; //10^9 war zu viel...
    int secToNs = 1000000000;

    clock_gettime(CLOCK_MONOTONIC_RAW,&loopStart);
    for(int i = 0; i < iterations; i++)
    {
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&loopEnd);

    long double avrLoopTime = ((long double) (loopEnd.tv_sec * secToNs + loopEnd.tv_nsec) - (long double) (loopStart.tv_sec * secToNs + loopStart.tv_nsec))/(long double) iterations;
    
    clock_gettime(CLOCK_MONOTONIC_RAW,&clockStart);
    for(int i = 0; i < iterations; i++)
    {
        read(0,NULL,0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&clockEnd);

    long double avrRead = ((long double) (clockEnd.tv_sec * secToNs + clockEnd.tv_nsec) - (long double) (clockStart.tv_sec * secToNs + clockStart.tv_nsec))/(long double) iterations;
    avrRead = avrRead - avrLoopTime;

    
    clock_gettime(CLOCK_MONOTONIC_RAW,&clockErrS);
    for(int i = 0; i < iterations; i++)
    {
        if(read(0,NULL,0) < 0)
        {
            fprintf(stderr,"Read Failed\n");
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&clockErrE);

    long double avrErrRead = ((long double) (clockErrE.tv_sec * secToNs + clockErrE.tv_nsec) - (long double) (clockErrS.tv_sec * secToNs + clockErrS.tv_nsec))/(long double) iterations;
    avrErrRead = avrErrRead - avrLoopTime;
    
    printf("Durchschnittliche Dauer einer Schleife in: %Lf nsec\n", avrLoopTime);
    printf("Durchschnittliche Dauer eines 0ByteReads in: %Lf nsec\n", avrRead);
    printf("Durchschnittliche Dauer eines 0ByteReads mit Fehler Behandlung in: %Lf nsec\n", avrErrRead);
    return 0;
}