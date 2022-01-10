#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"

//
// Here, you have to write (almost) ALL the code. Oh no!
// How can you show that a thread does not starve
// when attempting to acquire this mutex you build?
//

typedef struct __ns_mutex_t {
    int room1;
    int room2;
    sem_t key1;
    sem_t key2;
    sem_t crit;
} ns_mutex_t;

void ns_mutex_init(ns_mutex_t *m) {
    m->room1 = 0;
    m->room2 = 0;
    sem_init(&m->key1, 0, 1);
    sem_init(&m->key2, 0, 1);
    sem_init(&m->crit, 0, 1);
}

void ns_mutex_acquire(ns_mutex_t *m) {
    sem_wait(&m->key1);
    m->room1++;
    sem_post(&m->key1);

    sem_wait(&m->key2);
    sem_wait(&m->key1);
    m->room1--;
    m->room2++;
    
    if (m->room1 == 0) {
        sem_post(&m->key1);
        sem_post(&m->crit);
    } else
    {
        sem_post(&m->key1);
        sem_post(&m->key2);
    }
    sem_wait(&m->crit);
}

void ns_mutex_release(ns_mutex_t *m) {
    m->room2--;
    if (m->room2 == 0) {
        sem_post(&m->key2);
    } else
    {
        sem_post(&m->crit);
    }
}

int loops;
ns_mutex_t mutex;

typedef struct __tinfo_t {
    int thread_id;
} tinfo_t;

void *worker(void *arg) {
    tinfo_t *t = (tinfo_t *) arg;
    for (int i = 0; i < loops; i++) {
        printf("T%d :before %d\n",t->thread_id, i);
        ns_mutex_acquire(&mutex);
        printf("T%d :after %d\n",t->thread_id, i);
        ns_mutex_release(&mutex);
    }

    return NULL;
}



int main(int argc, char *argv[]) {
    printf("parent: begin\n");
    assert(argc == 3);
    int num_threads = atoi(argv[1]);
    loops = atoi(argv[2]);
    

    pthread_t t[num_threads];
    tinfo_t ti[num_threads];

    ns_mutex_init(&mutex);
    int i;
    for (i = 0; i < num_threads; i++) {
        ti[i].thread_id = i;
        Pthread_create(&t[i], NULL, worker, NULL);
    }

    for (i = 0; i < num_threads; i++) {
        Pthread_join(t[i], NULL);
    }

    printf("parent: end\n");
    return 0;
}