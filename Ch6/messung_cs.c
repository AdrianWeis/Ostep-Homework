#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main()
{
    struct timespec loopStart,loopEnd,clockChildStart,clockChildEnd,clockParentStart,clockParentEnd;
    int iterations = 10000000; //10^9 war zu viel...
    int pipeFd1[2], pipeFd2[2];

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(7, &mask);
    sched_setaffinity(0, sizeof(cpu_set_t), &mask);

    if (pipe(pipeFd1) < 0)
    {
      perror("pipe");
      exit(EXIT_FAILURE);
    }

    if (pipe(pipeFd2) < 0)
    {
      perror("pipe");
      exit(EXIT_FAILURE);
    }

    clock_gettime(CLOCK_MONOTONIC_RAW,&loopStart);
    for(int i = 0; i < iterations; i++)
    {
        read(0,NULL,0);
        write(0,NULL,0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&loopEnd);

    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW,&clockChildStart);
        for(int i = 0; i < iterations; i++)
        {
            read(pipeFd1[0],NULL,0);
            write(pipeFd2[1],NULL,0);
        }
        clock_gettime(CLOCK_MONOTONIC_RAW,&clockChildEnd);
    } else
    {
        clock_gettime(CLOCK_MONOTONIC_RAW,&clockParentStart);
        for(int i = 0; i < iterations; i++)
        {
            read(pipeFd2[0],NULL,0);
            write(pipeFd1[1],NULL,0);
        }
        clock_gettime(CLOCK_MONOTONIC_RAW,&clockParentEnd);
    }

    long double avrLoopTime = ((long double) loopEnd.tv_nsec - (long double) loopStart.tv_nsec)/(long double) iterations;
    long double avrChildTime = ((long double) clockChildEnd.tv_nsec - (long double) clockChildStart.tv_nsec)/(long double) iterations;
    long double avrParentTime = ((long double) clockParentEnd.tv_nsec - (long double) clockParentStart.tv_nsec)/(long double) iterations;
    avrChildTime -= avrLoopTime;
    avrParentTime -= avrLoopTime;

    printf("Durchschnittliche Dauer einer Schleife in: %Lf nsec\n", avrLoopTime);
    printf("Durchschnittliche Dauer des Context-Switch vom Kind in: %Lf nsec\n", avrChildTime);
    printf("Durchschnittliche Dauer des Context-Switch von Eltern in: %Lf nsec\n", avrParentTime);

    return 0;
}