#include "c29.h"
#include <stdio.h>

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

typedef struct { int time; } myret_t;


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

void *worker(void *arg) {
    struct timespec start,end;
    counter_t *c = (counter_t*) arg;
    myret_t* rvals = malloc(sizeof(myret_t));
    assert(rvals != NULL);

    //printf("I am before the loop\n");

    clock_gettime(CLOCK_MONOTONIC_RAW,&start);
    for(int i = 0; i < LOOPS; i++)
    {
        /* if(i%10 == 0){
            printf("I am in mod 10 of the loop\n");
        } */
        increment(c);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);

    //printf("I am after the loop\n");
    rvals->time = calcTime(start,end,LOOPS);
    return (void *) rvals;
}


int main()
{

    /* cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(1, &mask);
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask); */

    pthread_t p;
    counter_t *count = malloc(sizeof(counter_t));
    assert(count != NULL);
    init(count);
    myret_t *rvals;
    //int loops = LOOPS;
    Pthread_create(&p, NULL, worker, count);
    
    Pthread_join(p, (void **) &rvals);
    printf("Average Increment: %ld ns\n", rvals->time);
    printf("Counter at: %d\n", count->value);
    free(rvals);
    return 0;

}