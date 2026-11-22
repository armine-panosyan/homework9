#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define THREAD_COUNT 3

void *run_thread(void *arg)
{
    int id = *(int *)arg;
    printf("Thread %d is running\n", id);
    return NULL;
}

int main(void)
{
    pthread_t threads[THREAD_COUNT];
    int ids[THREAD_COUNT] = {1, 2, 3};
    int created = 0;
    int status = EXIT_SUCCESS;

    for (int i = 0; i < THREAD_COUNT; i++) {
        int error = pthread_create(&threads[i], NULL, run_thread, &ids[i]);
        if (error != 0) {
            fprintf(stderr, "pthread_create failed: %s\n", strerror(error));
            status = EXIT_FAILURE;
            break;
        }
        created++;
    }

    for (int i = 0; i < created; i++) {
        int error = pthread_join(threads[i], NULL);
        if (error != 0) {
            fprintf(stderr, "pthread_join failed: %s\n", strerror(error));
            status = EXIT_FAILURE;
        }
    }

    return status;
}
