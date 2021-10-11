#include <time.h>

int main()
{
    struct timespec loopStart,loopEnd,clockStart,clockEnd;
    int iterations = 1000000000;

    clock_gettime(CLOCK_MONOTONIC_RAW,&loopStart);
    for(int i = 0, i < iterations, i++)
    {

    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&loopEnd);

    double avrLoopTime = (loopStart.tv_nsec - loopEnd.tv_nsec)/iterations;
    printf("Durchschnittliche Dauer einer Schleife in: %d nsec");
}