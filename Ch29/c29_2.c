#include "c29.h"
#include <stdlib.h>

typedef struct __counter_t {
    int value;
    pthread_mutex_t lock;
} counter_t;

typedef struct { long time; } myret_t;

typedef struct { counter_t* c; int loop; } myargs;

void init(counter_t *c) {
    c->value = 0;
    Pthread_mutex_init(&c->lock, NULL);
}

void initArg(myargs *arg, counter_t* c, int tAnz) {
    arg->c = c;
    arg->loop = LOOPS; ///tAnz;
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
    myargs * args = (myargs *) arg;
    counter_t *c = args->c;
    int loop = args->loop;
    myret_t* rvals = malloc(sizeof(myret_t));
    assert(rvals != NULL);

    clock_gettime(CLOCK_MONOTONIC_RAW,&start);
    for(int i = 0; i < loop; i++)
    {
        increment(c);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);

    rvals->time = calcTime(start,end,1);//loop);
    return (void *) rvals;
}


int main(int argc, char*argv[]) {

    if (argc != 2){
        printf("Fehlerhafteraufruf: c29_2 threadAnz\n");
        return -1;
    }
    
    int tAnz = atoi(argv[1]);
    if (tAnz > 4 || tAnz < 1) {     
        tAnz = 1;
    }

    //printf("Number of CPUs: %ld\n", sysconf(_SC_NPROCESSORS_CONF));

    counter_t *count = malloc(sizeof(counter_t));
    assert(count != NULL);
    init(count);
    myargs *arg = malloc(sizeof(myargs));
    assert(count != NULL);
    initArg(arg,count,tAnz);

    if(tAnz == 2) {
        pthread_t p1,p2;

        myret_t *rvals1;
        myret_t *rvals2;
        Pthread_create(&p1, NULL, worker, arg);
        Pthread_create(&p2, NULL, worker, arg);
        Pthread_join(p1, (void **) &rvals1);
        Pthread_join(p2, (void **) &rvals2);
        
        /* printf("Average Increment Time p1: %ld ns\n", rvals1->time);
        printf("Average Increment Time p2: %ld ns\n", rvals2->time);
        printf("Counter at: %d\n", count->value); */
        printf("Average with in the threads: %ld\n", (rvals1->time+rvals2->time));//tAnz);
        free(rvals1);
        free(rvals2);
    } else if (tAnz == 3) {
        pthread_t p1,p2,p3;

        myret_t * rvals1;
        myret_t *rvals2;
        myret_t *rvals3;

        Pthread_create(&p1, NULL, worker, arg);
        Pthread_create(&p2, NULL, worker, arg);
        Pthread_create(&p3, NULL, worker, arg);
        Pthread_join(p1, (void **) &rvals1);
        Pthread_join(p2, (void **) &rvals2);
        Pthread_join(p3, (void **) &rvals3);
        
        /* printf("Average Increment Time p1: %ld ns\n", rvals1->time);
        printf("Average Increment Time p2: %ld ns\n", rvals2->time);
        printf("Average Increment Time p3: %ld ns\n", rvals3->time); 
        printf("Counter at: %d\n", count->value);*/
        printf("Average with in the threads: %ld\n", (rvals1->time+rvals2->time+rvals3->time));//tAnz);
        free(rvals1);
        free(rvals2);
        free(rvals3);
    } else if (tAnz == 4) {
        pthread_t p1,p2,p3,p4;
        
        myret_t * rvals1;
        myret_t *rvals2;
        myret_t *rvals3;
        myret_t *rvals4;

        Pthread_create(&p1, NULL, worker, arg);
        Pthread_create(&p2, NULL, worker, arg);
        Pthread_create(&p3, NULL, worker, arg);
        Pthread_create(&p4, NULL, worker, arg);
        Pthread_join(p1, (void **) &rvals1);
        Pthread_join(p2, (void **) &rvals2);
        Pthread_join(p3, (void **) &rvals3);
        Pthread_join(p4, (void **) &rvals4);
        
        /* printf("Average Increment Time p1: %ld ns\n", rvals1->time);
        printf("Average Increment Time p2: %ld ns\n", rvals2->time);
        printf("Average Increment Time p3: %ld ns\n", rvals3->time);
        printf("Average Increment Time p4: %ld ns\n", rvals4->time);
        printf("Counter at: %d\n", count->value); */
        printf("Average with in the threads: %ld\n", (rvals4->time+rvals1->time+rvals2->time+rvals3->time));//tAnz);
        free(rvals1);
        free(rvals2);
        free(rvals3);
        free(rvals4);
    } else {
        pthread_t p1;
        
        myret_t *rvals1;
        Pthread_create(&p1, NULL, worker, arg);
        Pthread_join(p1, (void **) &rvals1);
        
        printf("Average Increment Time with one thread: %ld ns\n", rvals1->time);
        //printf("Counter at: %d\n", count->value);
        free(rvals1);
    }
    free(arg);
    return 0;

}