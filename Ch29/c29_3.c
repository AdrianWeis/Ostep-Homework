#include "c29.h"

typedef struct __counter_t {
    int global; // global count
    pthread_mutex_t glock; // global lock
    int local[NUMCPUS]; // per-CPU count
    pthread_mutex_t llock[NUMCPUS]; // ... and locks
    int threshold; // update frequency
} counter_t;

typedef struct { long time; } myret_t;

typedef struct { counter_t* c; int thread; int loop} myargs;

// init: record threshold, init locks, init values
// of all local counts and global count
void init(counter_t *c, int threshold) {
    c->threshold = threshold;
    c->global = 0;
    Pthread_mutex_init(&c->glock, NULL);
    int i;
    for (i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
    	Pthread_mutex_init(&c->llock[i], NULL);
    }
}

void initArg(myargs * arg, counter_t * c, int thread, int tAnz) {
    arg->loop = LOOPS/tAnz;
    arg->thread = thread;
    arg->c = c;
}
// update: usually, just grab local lock and update
// local amount; once local count has risen ’threshold’,
// grab global lock and transfer local values to it
void update(counter_t *c, int threadID, int amt) {
    int cpu = threadID % NUMCPUS;
    Pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold) {
        // transfer to global (assumes amt>0)
        Pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        Pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    Pthread_mutex_unlock(&c->llock[cpu]);
}

// get: just return global amount (approximate)
int get(counter_t *c) {
    Pthread_mutex_lock(&c->glock);
    int val = c->global;
    Pthread_mutex_unlock(&c->glock);
    return val; // only approximate!
}

void *worker(void *arg) {
    struct timespec start,end;
    myargs *args = (myargs*) arg;
    counter_t * c = args->c;
    int tID = args->thread;
    myret_t* rvals = malloc(sizeof(myret_t));
    assert(rvals != NULL);

    clock_gettime(CLOCK_MONOTONIC_RAW,&start);
    for(int i = 0; i < LOOPS; i++)
    {
        update(c,tID,1);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);

    rvals->time = calcTime(start,end,LOOPS);
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

    printf("Number of CPUs: %d\n", NUMCPUS);

    /*cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(1, &mask);
    sched_setaffinity(getpid(), sizeof(cpu_set_t), &mask); */

    counter_t *count = malloc(sizeof(counter_t));
    assert(count != NULL);
    init(count,5);

    if(tAnz == 2) {
        pthread_t p1,p2;
        
        myret_t *rvals1;
        myret_t *rvals2;

        myargs * arg1=malloc(sizeof(myargs));
        assert(arg1 != NULL);
        initArg(arg1, count, 0, tAnz);
        myargs * arg2=malloc(sizeof(myargs));
        assert(arg2 != NULL);
        initArg(arg2, count, 1, tAnz);
        //int loops = LOOPS;
        Pthread_create(&p1, NULL, worker, arg1);
        Pthread_create(&p2, NULL, worker, arg2);
        Pthread_join(p1, (void **) &rvals1);
        Pthread_join(p2, (void **) &rvals2);
        
        printf("Average Increment Time p1: %ld ns\n", rvals1->time);
        printf("Average Increment Time p2: %ld ns\n", rvals2->time);
        //printf("Counter at: %d\n", count->value);
        printf("Average with in the threads: %ld\n", (rvals1->time+rvals2->time)/tAnz);
        free(rvals1);
        free(rvals2);
        free(arg1);
        free(arg2);
    } else if (tAnz == 3) {
        pthread_t p1,p2,p3;
        
        myret_t * rvals1;
        myret_t *rvals2;
        myret_t *rvals3;

        myargs * arg1=malloc(sizeof(myargs));
        assert(arg1 != NULL);
        initArg(arg1, count, 0, tAnz);
        myargs * arg2=malloc(sizeof(myargs));
        assert(arg2 != NULL);
        initArg(arg2, count, 1, tAnz);
        myargs * arg3=malloc(sizeof(myargs));
        assert(arg3 != NULL);
        initArg(arg3, count, 2, tAnz);
        //int loops = LOOPS;
        Pthread_create(&p1, NULL, worker, arg1);
        Pthread_create(&p2, NULL, worker, arg2);
        Pthread_create(&p3, NULL, worker, arg3);
        Pthread_join(p1, (void **) &rvals1);
        Pthread_join(p2, (void **) &rvals2);
        Pthread_join(p3, (void **) &rvals3);
        
        printf("Average Increment Time p1: %ld ns\n", rvals1->time);
        printf("Average Increment Time p2: %ld ns\n", rvals2->time);
        printf("Average Increment Time p3: %ld ns\n", rvals3->time);
        printf("Counter at: %d\n", count->global);
        printf("Average with in the threads: %ld\n", (rvals1->time+rvals2->time+rvals3->time)/tAnz);
        free(rvals1);
        free(rvals2);
        free(rvals3);
        free(arg1);
        free(arg2);
        free(arg3);
    } else if (tAnz == 4) {
        pthread_t p1,p2,p3,p4;
        
        myret_t * rvals1;
        myret_t *rvals2;
        myret_t *rvals3;
        myret_t *rvals4;

        myargs * arg1=malloc(sizeof(myargs));
        assert(arg1 != NULL);
        initArg(arg1, count, 0, tAnz);
        myargs * arg2=malloc(sizeof(myargs));
        assert(arg2 != NULL);
        initArg(arg2, count, 1, tAnz);
        myargs * arg3=malloc(sizeof(myargs));
        assert(arg3 != NULL);
        initArg(arg3, count, 2, tAnz);
        myargs * arg4=malloc(sizeof(myargs));
        assert(arg4 != NULL);
        initArg(arg4, count, 3, tAnz);
        //int loops = LOOPS;
        Pthread_create(&p1, NULL, worker, arg1);
        Pthread_create(&p2, NULL, worker, arg2);
        Pthread_create(&p3, NULL, worker, arg3);
        Pthread_create(&p4, NULL, worker, arg4);
        Pthread_join(p1, (void **) &rvals1);
        Pthread_join(p2, (void **) &rvals2);
        Pthread_join(p3, (void **) &rvals3);
        Pthread_join(p4, (void **) &rvals4);
        
        printf("Average Increment Time p1: %ld ns\n", rvals1->time);
        printf("Average Increment Time p2: %ld ns\n", rvals2->time);
        printf("Average Increment Time p3: %ld ns\n", rvals3->time);
        printf("Average Increment Time p4: %ld ns\n", rvals4->time);
        printf("Counter at: %d\n", count->global);
        printf("Average with in the threads: %ld\n", (rvals4->time+rvals1->time+rvals2->time+rvals3->time)/tAnz);
        free(rvals1);
        free(rvals2);
        free(rvals3);
        free(rvals4);
        free(arg1);
        free(arg2);
        free(arg3);
        free(arg4);
    } else {
        pthread_t p1;
        
        myret_t *rvals1;
        myargs * arg1=malloc(sizeof(myargs));
        assert(arg1 != NULL);
        initArg(arg1, count, 0, tAnz);
        //int loops = LOOPS;
        Pthread_create(&p1, NULL, worker, arg1);
        Pthread_join(p1, (void **) &rvals1);
        
        printf("Average Increment Time with one thread: %ld ns\n", rvals1->time);
        printf("Counter at: %d\n", count->global);
        free(rvals1);
        free(arg1);
    }
    return 0;
}