// tlb.c - Adrian Weishaupt, Simon Kaemmer - Gruppe 29

#define _GNU_SOURCE 
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tlb.h"

int main(int argc, char *argv[])
{

    cpu_set_t set;
    
    //Trying to get a single CPU to ensure function on BSYS-Container
    for(int i = 0; i < sysconf(_SC_NPROCESSORS_CONF); i++) {

        CPU_ZERO(&set);
        CPU_SET(i, &set);

        if(sched_setaffinity(0, sizeof(cpu_set_t), &set) == 0) {
            break;
        }
    }

/*
    if(argc != 3) {
        fprintf(stderr, "./tlb [NUMPAGES] [LOOPS]\n");
        exit(0);
    }


    const int NUMPAGES = atoi(argv[1]);
    const int LOOPS = atoi(argv[2]); */

    const long PAGESIZE = sysconf(_SC_PAGE_SIZE);

    int NUMPAGES = 4;
    int LOOPS = 1000000;
    int opt;

    while((opt = getopt(argc, argv, "n:l:h")) != -1) {

        switch(opt) {
            case 'n':
                NUMPAGES = atoi(optarg);
                break;
            case 'l':
                LOOPS = atoi(optarg);
                break;
            case 'h':
                printf("/.tlb [ARGS]\n\n");
                printf("    -n : Number of Pages to iterate. (Example: /.tlb -n 100) - Default: 4\n");
                printf("    -l : Number of trials to get a good value. (Example: /.tlb -l 100000 - Default: 1000000\n\n");
                printf("There should be a Python3-Script to start from 1 pageaccess up to 2048 accesses.\n");
                printf("Make sure you have matplotlib for Python3 installed to run the script! \n\n");
                printf("Run the Python3-Script by typing ./script.py or python3 script.py\n");
                printf("Try ./script.py -h to get more information.\n\n\n");
                printf("Author: Adrian Weishaupt, Simon Kaemmer\n\n");
                exit(0);
            case '?':
                printf("Unknown Option. Use -h for help! \n");
                exit(0);                
        }
    }

    if(PAGESIZE <= 0) {
        fprintf(stderr, "Pagesize could not be read\n");
        exit(0);
    }

    if(NUMPAGES <= 0) {
        fprintf(stderr, "Missing valid number of pages\n");
        exit(0);
    }

    if(LOOPS <= 0) { 
        fprintf(stderr, "Missing valid number of loops\n");
        exit(0);
    }

    printf("Numpages: %d    Loops: %d\n", NUMPAGES, LOOPS);

    long averageTime = measureOverheadAverage(LOOPS, NUMPAGES);
    long overhead = measureOverhead(LOOPS, NUMPAGES);

    long averagePage = measurePagingAverage(PAGESIZE, NUMPAGES, LOOPS);
    long timeMinMax = measurePagingMinMax(PAGESIZE, NUMPAGES, LOOPS);
    long time = measurePaging(PAGESIZE, NUMPAGES, LOOPS, averagePage);


    printf("Time from Loop: %ld\n", averageTime);
    printf("Time from Clock_Gettime: %ld\n", overhead);

    printf("Time for Page Swap Average: %ld\n", averagePage - averageTime);

    printf("Time for Page Swap with MinMax: %ld\n", timeMinMax);
    printf("Time for Page Swap with MinMax: %ld\n", timeMinMax - overhead);

    printf("Time for Page Swap Average: %ld\n", time);
    printf("Time for Page Swap with 60percent Range: %ld\n", time - overhead);

    FILE *fp;
    fp = fopen("out.txt", "aw+");
    char str[10];
    sprintf(str, "%ld,", time-overhead);

    fputs(str, fp);

    fclose(fp);
    return 0;
}

// Array vorinitialisieren