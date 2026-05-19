#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_POOL_SIZE 4
#define TASK_QUEUE_SIZE 10

typedef struct {
    int task_id;
    int workload;
} Task;

Task task_queue[TASK_QUEUE_SIZE];
int task_count = 0;
int front = 0;

pthread_mutex_t queue_mutex;
pthread_cond_t queue_cond;

int shutdown_flag = 0;

void* worker(void* arg) {

    long id = (long)arg;

    while (1) {

        pthread_mutex_lock(&queue_mutex);

        while (task_count == 0 && !shutdown_flag) {
            pthread_cond_wait(&queue_cond, &queue_mutex);
        }

        if (shutdown_flag && task_count == 0) {
            pthread_mutex_unlock(&queue_mutex);
            break;
        }

        Task task = task_queue[front++];
        task_count--;

        pthread_mutex_unlock(&queue_mutex);

        printf("Thread %ld processing Task %d\n", id, task.task_id);
        sleep(task.workload);
    }

    printf("Thread %ld exiting\n", id);
    return NULL;
}

void add_task(int id, int workload) {

    pthread_mutex_lock(&queue_mutex);

    task_queue[task_count].task_id = id;
    task_queue[task_count].workload = workload;
    task_count++;

    pthread_cond_signal(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);
}

int main() {

    pthread_t threads[THREAD_POOL_SIZE];

    pthread_mutex_init(&queue_mutex, NULL);
    pthread_cond_init(&queue_cond, NULL);

    for (long i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&threads[i], NULL, worker, (void*)i);
    }

    for (int i = 0; i < 6; i++) {
        add_task(i, (rand() % 3) + 1);
    }

    sleep(5);

    pthread_mutex_lock(&queue_mutex);
    shutdown_flag = 1;
    pthread_cond_broadcast(&queue_cond);
    pthread_mutex_unlock(&queue_mutex);

    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Thread pool shutdown complete\n");

    return 0;
}