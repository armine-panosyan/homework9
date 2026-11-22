#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *print_numbers(void *arg)
{
    int id = *(const int *)arg;

    for (int number = 1; number <= 5; number++) {
        printf("Thread %d: %d\n", id, number);
    }

    return NULL;
}

int main(void)
{
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};
    int created = 0;
    int status = EXIT_SUCCESS;

    for (int i = 0; i < 3; i++) {
        int error = pthread_create(&threads[i], NULL, print_numbers, &ids[i]);
        if (error != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(error));
            status = EXIT_FAILURE;
            break;
        }
        created++;
    }

    for (int i = 0; i < created; i++) {
        int error = pthread_join(threads[i], NULL);
        if (error != 0) {
            fprintf(stderr, "pthread_join: %s\n", strerror(error));
            status = EXIT_FAILURE;
        }
    }

    return status;
}
