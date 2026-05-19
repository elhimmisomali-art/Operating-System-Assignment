#include <stdio.h>
#include <pthread.h>

#define THREADS 5
#define ITERATIONS 100000

int counter = 0;

void* increment(void* arg) {

    for (int i = 0; i < ITERATIONS; i++) {
        counter++; // race condition
    }

    return NULL;
}

int main() {

    pthread_t t[THREADS];

    for (int i = 0; i < THREADS; i++) {
        pthread_create(&t[i], NULL, increment, NULL);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(t[i], NULL);
    }

    printf("Final Counter (UNSAFE) = %d\n", counter);

    return 0;
}