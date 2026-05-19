#include <stdio.h>
#include <pthread.h>

pthread_mutex_t A = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t B = PTHREAD_MUTEX_INITIALIZER;

void* thread1(void* arg) {

    pthread_mutex_lock(&A);
    pthread_mutex_lock(&B);

    printf("Thread 1 finished safely\n");

    pthread_mutex_unlock(&B);
    pthread_mutex_unlock(&A);

    return NULL;
}

void* thread2(void* arg) {

    pthread_mutex_lock(&A);
    pthread_mutex_lock(&B);

    printf("Thread 2 finished safely\n");

    pthread_mutex_unlock(&B);
    pthread_mutex_unlock(&A);

    return NULL;
}

int main() {

    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("No deadlock occurred\n");

    return 0;
}