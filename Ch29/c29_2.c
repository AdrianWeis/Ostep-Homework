#include "c29.h"

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;


void init(counter_t *c) {
    c->value = 0;
    Pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
    Pthread_mutex_lock(&c->lock);
    c->value++;
    Pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
    Pthread_mutex_lock(&c->lock);
    c->value--; 
    Pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
    Pthread_mutex_lock(&c->lock);
    int rc = c->value;
    Pthread_mutex_unlock(&c->lock);
    return rc;
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

void *worker(void *arg) {
    struct timespec start,end;
    counter_t *c = (counter_t*) arg;
    long* rvals = malloc(sizeof(long));
    assert(rvals != NULL);

    clock_gettime(CLOCK_MONOTONIC_RAW,&start);
    for(int i = 0; i < LOOPS; i++)
    {
        increment(c);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);

    long temp = calcTime(start,end,LOOPS);
    rvals = &temp;
    return (void *) rvals;
}


int main()
{

    /* cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(1, &mask);
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask); */

    pthread_t p;
    counter_t *c = malloc(sizeof(counter_t));
    assert(c != NULL);
    init(c);
    long *rvals;
    int error = 0;
    //int loops = LOOPS;
    Pthread_create(&p, NULL, worker, &c);
    
    Pthread_join(p, (void **) &rvals);
    printf("Average Increment: %ld ns\n", *rvals);
    free(rvals);
    return 0;

}