// tlb.h - Adrian Weishaupt, Simon Kaemmer - Gruppe 29

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>

#define BILLION 1000000000

// Function to calculate timedifference from stop to start with overflow handling
long calcTime(struct timespec start, struct timespec stop, int loops) {

    struct timespec res;
    // Check if nsec gets negative, and correct it
    if((stop.tv_nsec - start.tv_nsec) < 0) {
        res.tv_sec = stop.tv_sec - start.tv_sec -1; // Correct addition of 1Bil nanosecs
        res.tv_nsec = stop.tv_nsec - start.tv_nsec + BILLION;
    } else {
        res.tv_sec = stop.tv_sec - start.tv_sec;
        res.tv_nsec = stop.tv_nsec - start.tv_nsec;
    }

    return ((res.tv_sec * BILLION + res.tv_nsec) / loops);
}

// Function to measure TLB-Paging
long measurePagingAverage(long PAGESIZE, int NUMPAGES, int LOOPS) {

    struct timespec start, stop;

    // Array to loop through
    int *array = (int*) malloc(NUMPAGES * PAGESIZE);
    int jump = PAGESIZE / sizeof(int);

    for(int i = 0; i < NUMPAGES * jump; i += jump) { // Preinit for array
        array[i] = 0;
    }

    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);
    for(int i = 0; i < LOOPS; i++) {

        for(int j = 0; j < NUMPAGES * jump; j += jump) {

            array[j] += 1;
        }
    }
    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stop) == 0);


    free(array);
    return calcTime(start, stop, LOOPS*NUMPAGES);
}

long measurePaging(long PAGESIZE, int NUMPAGES, int LOOPS, long average)
{
    long counter = 0;
    long temp = 0;
    long resultTemp = 0;
    long averageMin = average*0.7;
    long averageMax = average*1.3;
    long result = 0;

    struct timespec start, stop;

    // Array to loop through
    int *array = (int*) malloc(NUMPAGES * PAGESIZE);
    assert(array != NULL);
    int jump = PAGESIZE / sizeof(int);

    for(int i = 0; i < NUMPAGES * jump; i += jump) { // Preinit for array
        array[i] = 0;
    }

    for(int i = 0; i < LOOPS; i++) 
    {
        for(int j = 0; j < NUMPAGES * jump; j += jump)
        {
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);
            array[j] += 1;
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stop) == 0);

            temp = calcTime(start, stop, 1);
            if (temp < averageMin || temp > averageMax) 
            {
                counter += 1;
                continue;
            }
            resultTemp += temp;
            
        }
        result += resultTemp/(NUMPAGES - counter);
        resultTemp = 0;
        counter = 0;
    }

    free(array);

    return result/LOOPS;
}

long measurePagingMinMax(long PAGESIZE, int NUMPAGES, int LOOPS, long average)
{
    long counter = 0;
    long resultTemp = 0;
    long min = average;
    long minDistance = 0;
    long maxDistance = 0;
    long max = average;
    long result = 0;

    long *timeArray = (long*) malloc(NUMPAGES * sizeof(long));
    assert(timeArray != NULL);

    struct timespec start, stop;

    // Array to loop through
    int *array = (int*) malloc(NUMPAGES * PAGESIZE);
    assert(array != NULL);
    int jump = PAGESIZE / sizeof(int);

    for(int i = 0; i < NUMPAGES * jump; i += jump) { // Preinit for array
        array[i] = 0;
    }

    for(int i = 0; i < LOOPS; i++) 
    {
        for(int j = 0; j < NUMPAGES * jump; j += jump)
        {
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);
            array[j] += 1;
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stop) == 0);

            timeArray[j] = calcTime(start, stop, 1);
            if (timeArray[j] < min) 
            {
                min = timeArray[j];
            }
            if (timeArray[j] > max) 
            {
                max = timeArray[j];
            }
            
        }

        minDistance = average - (average - min)*0.8; //10% der kleinsten Werte abschneiden
        maxDistance = average + (max - average)*0.8; //10% der größten Werte abschneiden

        for(int j = 0; j < NUMPAGES; j++)
        {
            if(timeArray[j] < minDistance || timeArray[j] > maxDistance)
            {
                timeArray[j] = 0;
                counter += 1;
            }
            resultTemp += timeArray[j];
        }

        result += resultTemp/(NUMPAGES - counter);
        min = average;
        max = average;
        resultTemp = 0;
        counter = 0;
    }

    free(timeArray);
    free(array);
    return result/LOOPS;
}

long measureOverheadAverage(int loops, int numpages) {

    struct timespec startBothFor, stopBothFor, start, stop;

    // Measure Both Loops
    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &startBothFor) == 0);
    for(int i = 0; i < loops; i++){
        for(int j = 0; j < numpages; j++)
        {
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stop) == 0);
        }
    }
    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stopBothFor) == 0);

    long timeBothLoops = calcTime(startBothFor, stopBothFor, loops*numpages);

    return timeBothLoops;
}

long measureOverhead(int loops, int numpages, long average) 
{
    long counter = 0;
    long temp = 0;
    long resultTemp = 0;
    long averageMin = average*0.7;
    long averageMax = average*1.3;
    long result = 0;
    struct timespec start, stop;

    for(int i = 0; i < loops; i++){
        for(int j = 0; j < numpages; j++)
        {
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stop) == 0);

            temp = calcTime(start, stop, 1);
            if (temp < averageMin || temp > averageMax) 
            {
                counter += 1;
                continue;
            }
            resultTemp += temp;
        }

        result += resultTemp/(numpages - counter);
        resultTemp = 0;
        counter = 0;
    }

    return result/loops;
}

