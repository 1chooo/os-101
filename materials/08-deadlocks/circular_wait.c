#include <pthread.h>
#include <stdio.h>

pthread_mutex_t first_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t second_mutex = PTHREAD_MUTEX_INITIALIZER;

void *do_work_one(void *param) {
    pthread_mutex_lock(&first_mutex);
    printf("Thread One: Acquired first_mutex.\n");
    pthread_mutex_lock(&second_mutex);
    printf("Thread One: Acquired second_mutex.\n");
    /* Simulate some work */
    printf("Thread One: Doing some work...\n");
    pthread_mutex_unlock(&second_mutex);
    printf("Thread One: Released second_mutex.\n");
    pthread_mutex_unlock(&first_mutex);
    printf("Thread One: Released first_mutex.\n");

    pthread_exit(0);
}

void *do_work_two(void *param) {
    pthread_mutex_lock(&second_mutex);
    printf("Thread Two: Acquired second_mutex.\n");
    pthread_mutex_lock(&first_mutex);
    printf("Thread Two: Acquired first_mutex.\n");
    /* Simulate some work */
    printf("Thread Two: Doing some work...\n");
    pthread_mutex_unlock(&first_mutex);
    printf("Thread Two: Released first_mutex.\n");
    pthread_mutex_unlock(&second_mutex);
    printf("Thread Two: Released second_mutex.\n");

    pthread_exit(0);
}

int main() {
    pthread_t thread_one, thread_two;
    
    pthread_create(&thread_one, NULL, do_work_one, NULL);
    pthread_create(&thread_two, NULL, do_work_two, NULL);

    pthread_join(thread_one, NULL);
    pthread_join(thread_two, NULL);

    return 0;
}
