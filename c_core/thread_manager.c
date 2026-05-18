#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_POOL_SIZE 4
#define MAX_TASKS 10

typedef struct {
    int task_id;
    int data;
} Task;

Task task_queue[MAX_TASKS];
int task_count = 0;

pthread_mutex_t lock;
pthread_cond_t cond;

void* worker(void* arg) {

    int thread_id = *(int*)arg;

    while (1) {

        pthread_mutex_lock(&lock);

        while (task_count == 0) {
            pthread_cond_wait(&cond, &lock);
        }

        Task task = task_queue[--task_count];

        pthread_mutex_unlock(&lock);

        printf("Thread %d processing task %d with data %d\n",
               thread_id, task.task_id, task.data);

        sleep(1);
    }

    return NULL;
}

int main() {

    pthread_t threads[THREAD_POOL_SIZE];
    int thread_ids[THREAD_POOL_SIZE];

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
    }

    
    for (int i = 0; i < 5; i++) {

        pthread_mutex_lock(&lock);

        task_queue[task_count].task_id = i + 1;
        task_queue[task_count].data = (i + 1) * 10;
        task_count++;

        pthread_mutex_unlock(&lock);

        pthread_cond_signal(&cond);
    }

    sleep(5);

    printf("Main thread finished\n");

    return 0;
}