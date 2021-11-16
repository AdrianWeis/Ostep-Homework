// tlb.h - Adrian Weishaupt, Simon Kaemmer - Gruppe 29

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>

#define BILLION 1000000000

typedef struct node{
    int data;
    struct node *ptr;
} node;

node* insert(node* head, int num) {
    node *temp, *prev, *next;
    temp = (node*)malloc(sizeof(node));
    temp->data = num;
    temp->ptr = NULL;

    //schon ein element?
    if(!head)
    {
        head=temp;
    } 
    else
    {
        prev = NULL;
        next = head;
        //liste durchlaufen um stelle zufinden
        while(next && next->data<=num)
        {
            prev = next;
            next = next->ptr;
        }

        //ende der liste
        if(!next)
        {
            prev->ptr = temp;
        } 
        else
        {
            if(prev)
            {
                temp->ptr = prev->ptr;
                prev-> ptr = temp;
            } 
            else 
            {
                temp->ptr = head;
                head = temp;
            }            
        }   
    }
    return head;
}

void free_list(node *head) {
    node *prev = head;
    node *cur = head;
    while(cur) {
        prev = cur;
        cur = prev->ptr;
        free(prev);
    }       
}

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

//measure with sorted list

long measurePagingList(long PAGESIZE, int NUMPAGES, int LOOPS) 
{
    struct timespec start, stop;
    double resultTemp = 0;
    double result = 0;
    int counter = 0;
    node *head, *p;
    head = NULL;

    // Array to loop through
    int *array = (int*) malloc(NUMPAGES * PAGESIZE);
    assert(array != NULL);
    int jump = PAGESIZE / sizeof(int);

    for(int i = 0; i < NUMPAGES * jump; i += jump) { // Preinit for array
        array[i] = 0;
    }

    for(int i = 0; i < LOOPS; i++) 
    {
        head = NULL;
        for(int j = 0; j < NUMPAGES * jump; j += jump)
        {
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);
            array[j] += 1;
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stop) == 0);

            head = insert(head, calcTime(start, stop, 1));
        }

        //10% der kleinsten und größten werte abschneiden
        p = head;
        for(int i = 0; i < NUMPAGES; i++)
        {
            if(i > (NUMPAGES*0.1) || i < (NUMPAGES*0.9))
            {
                resultTemp += p->data;
                counter++;
            }
            p = p->ptr;
        }
        result = resultTemp/counter;
        resultTemp = 0;
        counter = 0;
        free_list(head);
    }

    

    
    free(array);
    return result/LOOPS;
}

long measureOverheadList(int LOOPS, int NUMPAGES)
{
    struct timespec start, stop;
    double resultTemp = 0;
    double result = 0;
    int counter = 0;
    node *head, *p;
    head = NULL;

    for(int i = 0; i < LOOPS; i++){
        head =NULL;
        for(int j = 0; j < NUMPAGES; j++)
        {
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stop) == 0);

            head = insert(head,calcTime(start, stop, 1));
        }
        //10% der kleinsten und größten werte abschneiden
        p = head;
        for(int i = 0; i < NUMPAGES; i++)
        {
            if(i > (NUMPAGES*0.1) || i < (NUMPAGES*0.9))
            {
                resultTemp += p->data;
                counter++;
            }
            p = p->ptr;
        }
        result = resultTemp/counter;
        resultTemp = 0;
        counter = 0;
        free_list(head);
    }

    return result/(LOOPS * NUMPAGES * 0.8);
}

// Function to measure TLB-Paging simple

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

long measureOverheadAverage(int LOOPS, int NUMPAGES) {

    struct timespec startBothFor, stopBothFor;

    // Measure Both Loops
    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &startBothFor) == 0);
    for(int i = 0; i < LOOPS; i++){
        for(int j = 0; j < NUMPAGES; j++)
        {
            
        }
    }
    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stopBothFor) == 0);

    long timeBothLoops = calcTime(startBothFor, stopBothFor, LOOPS*NUMPAGES);

    return timeBothLoops;
}

//With Min and Max

long measurePagingMinMax(long PAGESIZE, int NUMPAGES, int LOOPS)
{
    long counter = 0;
    double resultTemp = 0;
    int temp = 0;
    long min = 0;
    double average = 0;
    int minMaxFilter = 0;
    long max = 0;
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

            temp = j/jump;
            timeArray[temp] = calcTime(start, stop, 1);
            if (j == 0) 
            {
                min = timeArray[0];
                max = timeArray[0];
            }
            else if (timeArray[temp] < min) 
            {
                min = timeArray[temp];
            }
            else if (timeArray[temp] > max) 
            {
                max = timeArray[temp];
            }
            average += timeArray[temp];
            
        }

        average = average/NUMPAGES;
        
        minMaxFilter = (max-min)/10;

        for(int j = 0; j < NUMPAGES; j++)
        {
            if(timeArray[j] > max - minMaxFilter) //beim min auch filtern?
            {
                timeArray[j] = 0;
                counter += 1;
            }
            resultTemp += timeArray[j];
        }

        if(NUMPAGES - counter > 0) {
            result += resultTemp/(NUMPAGES - counter);
        }

        resultTemp = 0;
        counter = 0;
    }

    free(timeArray);
    free(array);
    return result/LOOPS;
}

long measureOverheadMinMax(int LOOPS, int NUMPAGES) 
{
    long counter = 0;
    double resultTemp = 0;
    long min = 0;
    double average = 0;
    int minMaxFilter = 0;
    long max = 0;
    double result = 0;

    long *timeArray = (long*) malloc(NUMPAGES * sizeof(long));
    assert(timeArray != NULL);

    struct timespec start, stop;

    for(int i = 0; i < LOOPS; i++){
        for(int j = 0; j < NUMPAGES; j++)
        {
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stop) == 0);

            timeArray[j] = calcTime(start, stop, 1);
            if (j == 0) 
            {
                min = timeArray[0];
                max = timeArray[0];
            }
            else if (timeArray[j] < min) 
            {
                min = timeArray[j];
            }
            else if (timeArray[j] > max) 
            {
                max = timeArray[j];
            }
            average += timeArray[j];
            
        }

        average = average/NUMPAGES;
        

        minMaxFilter = (max-min)/10;

        for(int j = 0; j < NUMPAGES; j++)
        {
            if(timeArray[j] > max - minMaxFilter)
            {
                timeArray[j] = 0;
                counter += 1;
            }
            resultTemp += timeArray[j];
        }

        if(NUMPAGES - counter > 0) {
            result += resultTemp/(NUMPAGES - counter);
        }

        resultTemp = 0;
        counter = 0;
    }

    free(timeArray);

    return (long)(result/LOOPS);
}

