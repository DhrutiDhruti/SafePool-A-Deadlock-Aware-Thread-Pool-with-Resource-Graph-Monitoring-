#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "thpool.h"

static void* thread_do_work(void* arg) {
threadpool tp = (threadpool)arg;
while (1) {
pthread_mutex_lock(&tp->lock);
    while (tp->job_queue_head == NULL && !tp->stop)
        pthread_cond_wait(&tp->notify, &tp->lock);

    if (tp->stop) {
        pthread_mutex_unlock(&tp->lock);
        break;
    }

    job_t* job = tp->job_queue_head;
    if (job) {
        tp->job_queue_head = job->next;
        if (!tp->job_queue_head)
            tp->job_queue_tail = NULL;
    }

    pthread_mutex_unlock(&tp->lock);

    if (job) {
        job->function(job->arg);
        free(job);
    }
}
return NULL;
}

threadpool thpool_init(int num_threads) {
threadpool tp = malloc(sizeof(struct threadpool));
tp->thread_count = num_threads;
tp->threads = malloc(sizeof(pthread_t) * num_threads);
tp->job_queue_head = NULL;
tp->job_queue_tail = NULL;
tp->stop = 0;
pthread_mutex_init(&tp->lock, NULL);
pthread_cond_init(&tp->notify, NULL);

for (int i = 0; i < num_threads; i++)
    pthread_create(&tp->threads[i], NULL, thread_do_work, (void*)tp);

return tp;
}

void thpool_add_work(threadpool tp, void (*function)(void*), void* arg) {
job_t* job = malloc(sizeof(job_t));
job->function = function;
job->arg = arg;
job->next = NULL;

pthread_mutex_lock(&tp->lock);
if (!tp->job_queue_head) {
    tp->job_queue_head = job;
    tp->job_queue_tail = job;
} else {
    tp->job_queue_tail->next = job;
    tp->job_queue_tail = job;
}
pthread_cond_signal(&tp->notify);
pthread_mutex_unlock(&tp->lock);
}

void thpool_wait(threadpool tp) {
while (1) {
pthread_mutex_lock(&tp->lock);
int idle = (tp->job_queue_head == NULL);
pthread_mutex_unlock(&tp->lock);
if (idle) break;
sleep(1);
}
}

void thpool_destroy(threadpool tp) {
pthread_mutex_lock(&tp->lock);
tp->stop = 1;
pthread_cond_broadcast(&tp->notify);
pthread_mutex_unlock(&tp->lock);
for (int i = 0; i < tp->thread_count; i++)
    pthread_join(tp->threads[i], NULL);

free(tp->threads);
pthread_mutex_destroy(&tp->lock);
pthread_cond_destroy(&tp->notify);
free(tp);
}

