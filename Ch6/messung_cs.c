#define _GNU_SOURCE
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/wait.h>

int main()
{
    struct timespec loopStart,loopEnd,clockChildStart,clockChildEnd,clockParentStart,clockParentEnd;
    struct timespec forS,forE,readS,readE,writeS,writeE;
    int iterations = 10000000; //10^9 war zu viel...
    int secToNs = 1000000000;

    int pipeFd1[2], pipeFd2[2];
    
    //Potenziele Fehlerquelle, funktionsweise nachprüfen, evtl. im kind und parent setzen
    

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

    
    clock_gettime(CLOCK_MONOTONIC_RAW,&forS);
    for(int i = 0; i < iterations; i++)
    {
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&forE);


    long double avrForTime = ((long double) (forE.tv_sec * secToNs + forE.tv_nsec) - (long double) (forS.tv_sec * secToNs + forS.tv_nsec))/(long double) iterations;
    
    clock_gettime(CLOCK_MONOTONIC_RAW,&readS);
    for(int i = 0; i < iterations; i++)
    {
        read(0,NULL,0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&readE);

    
    long double avrReadTime = ((long double) (readE.tv_sec * secToNs + readE.tv_nsec) - (long double) (readS.tv_sec * secToNs + readS.tv_nsec))/(long double) iterations;
    
    clock_gettime(CLOCK_MONOTONIC_RAW,&writeS);
    for(int i = 0; i < iterations; i++)
    {
        write(0,NULL,0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&writeE);

    long double avrWriteTime = ((long double) (writeE.tv_sec * secToNs + writeE.tv_nsec) - (long double) (writeS.tv_sec * secToNs + writeS.tv_nsec))/(long double) iterations;
    
    clock_gettime(CLOCK_MONOTONIC_RAW,&loopStart);
    for(int i = 0; i < iterations; i++)
    {
        read(0,NULL,0);
        write(0,NULL,0);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&loopEnd);

    long double avrLoopTime = ((long double) (loopEnd.tv_sec * secToNs + loopEnd.tv_nsec) - (long double) (loopStart.tv_sec * secToNs + loopStart.tv_nsec))/(long double) iterations;
    
    printf("Durchschnittliche Dauer einer Schleife in: %Lf nsec\n", avrLoopTime);
    printf("Differenz zu seperat testung: %Lf nsec", avrLoopTime-(avrReadTime-avrForTime)-(avrWriteTime-avrFortime)-avrFortime);

    int rc = fork();
    if(rc < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (rc == 0)
    {
        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(1, &mask);
        sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask);

        clock_gettime(CLOCK_MONOTONIC_RAW,&clockChildStart);
        for(int i = 0; i < iterations; i++)
        {
            read(pipeFd1[0],NULL,0);
            write(pipeFd2[1],NULL,0);
        }
        clock_gettime(CLOCK_MONOTONIC_RAW,&clockChildEnd);
        
        //printf("What does tv_sec mean: %ld\nAnd tv_nsec: %ld\n",clockChildEnd.tv_sec,clockChildEnd.tv_nsec);
        //printf("Versus Start tv_sec mean: %ld\nAnd tv_nsec: %ld\n",clockChildStart.tv_sec,clockChildStart.tv_nsec);
        
        long double start = (long double) (clockChildStart.tv_sec * secToNs + clockChildStart.tv_nsec);
        long double end = (long double) (clockChildEnd.tv_sec * secToNs + clockChildEnd.tv_nsec);
        long double avrChildTime = (end - start)/(long double) iterations;
        avrChildTime = avrChildTime - avrLoopTime;

        printf("Durchschnittliche Dauer des Context-Switch vom Kind in: %Lf nsec\n", avrChildTime);
    
    } else
    {
        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(1, &mask);
        sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask);

        clock_gettime(CLOCK_MONOTONIC_RAW,&clockParentStart);
        for(int i = 0; i < iterations; i++)
        {
            read(pipeFd2[0],NULL,0);
            write(pipeFd1[1],NULL,0);
        }
        clock_gettime(CLOCK_MONOTONIC_RAW,&clockParentEnd);

        long double start = (long double) (clockParentStart.tv_sec * secToNs + clockParentStart.tv_nsec);
        long double end = (long double) (clockParentEnd.tv_sec * secToNs + clockParentEnd.tv_nsec);
        long double avrParentTime = (end - start)/(long double) iterations;
        avrParentTime = avrParentTime - avrLoopTime;

        printf("Durchschnittliche Dauer des Context-Switch von Eltern in: %Lf nsec\n", avrParentTime);
        wait(NULL);
    }
   
    return 0;
}