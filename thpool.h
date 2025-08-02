#ifndef THPOOL_H
#define THPOOL_H

#include <pthread.h>

typedef struct job {
void (*function)(void*);
void* arg;
struct job* next;
} job_t;

typedef struct threadpool {
pthread_t* threads;
job_t* job_queue_head;
job_t* job_queue_tail;
pthread_mutex_t lock;
pthread_cond_t notify;
int thread_count;
int stop;
} *threadpool;

threadpool thpool_init(int num_threads);
void thpool_add_work(threadpool tp, void (*function)(void*), void* arg);
void thpool_wait(threadpool tp);
void thpool_destroy(threadpool tp);

#endif
