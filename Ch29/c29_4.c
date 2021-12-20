#include "c29.h"
#include <stdlib.h>

// basic node structure
typedef struct __node_t {
    int key;
    struct __node_t *next;
} node_t;

// basic list structure (one used per list)
typedef struct __list_t {
    node_t *head;
    pthread_mutex_t lock;
} list_t;

typedef struct myargs {
    list_t * l;
    int loop;
} myargs;

void initArg(myargs* arg,list_t *l, int tAnz)
{
    arg->l = l;
    arg->loop = LOOPS/tAnz;
}

typedef struct { long time; } myret_t;

void List_Init(list_t *L) {
    L->head = NULL;
    Pthread_mutex_init(&L->lock, NULL);
}

int List_Insert(list_t *L, int key) {
    Pthread_mutex_lock(&L->lock);
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        perror("malloc");
        Pthread_mutex_unlock(&L->lock);
        return -1; // fail
    }
    new->key = key;
    new->next = L->head;
    L->head = new;
    Pthread_mutex_unlock(&L->lock);
    return 0; // success
}

int List_Lookup(list_t *L, int key) {
    Pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr) {
        if (curr->key == key) {
            Pthread_mutex_unlock(&L->lock);
            return 0; // success
        }
        curr = curr->next;
    }
    Pthread_mutex_unlock(&L->lock);
    return -1; // failure
}

void *worker(void *arg) {
    struct timespec start,end;
    myargs *args = (myargs*) arg;
    list_t * l = args->l;
    int loop = args->loop;
    myret_t* rvals = malloc(sizeof(myret_t));
    assert(rvals != NULL);

    clock_gettime(CLOCK_MONOTONIC_RAW,&start);
    for(int i = 0; i < loop; i++)
    {
        List_Insert(l, rand()%1000);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW,&end);

    rvals->time = calcTime(start,end,loop);
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

    list_t *count = malloc(sizeof(list_t));
    assert(count != NULL);
    List_Init(count);

    if(tAnz == 2) {
        pthread_t p1,p2;
        
        myret_t *rvals1;
        myret_t *rvals2;

        myargs * arg1=malloc(sizeof(myargs));
        assert(arg1 != NULL);
        initArg(arg1, count, tAnz);
        myargs * arg2=malloc(sizeof(myargs));
        assert(arg2 != NULL);
        initArg(arg2, count, tAnz);
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
        initArg(arg1, count, tAnz);
        myargs * arg2=malloc(sizeof(myargs));
        assert(arg2 != NULL);
        initArg(arg2, count, tAnz);
        myargs * arg3=malloc(sizeof(myargs));
        assert(arg3 != NULL);
        initArg(arg3, count, tAnz);
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
        initArg(arg1, count, tAnz);
        myargs * arg2=malloc(sizeof(myargs));
        assert(arg2 != NULL);
        initArg(arg2, count, tAnz);
        myargs * arg3=malloc(sizeof(myargs));
        assert(arg3 != NULL);
        initArg(arg3, count, tAnz);
        myargs * arg4=malloc(sizeof(myargs));
        assert(arg4 != NULL);
        initArg(arg4, count, tAnz);
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
        initArg(arg1, count, tAnz);
        //int loops = LOOPS;
        Pthread_create(&p1, NULL, worker, arg1);
        Pthread_join(p1, (void **) &rvals1);
        
        printf("Average Increment Time with one thread: %ld ns\n", rvals1->time);
        free(rvals1);
        free(arg1);
    }
    return 0;
}