#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *print_square(void *arg)
{
    int number = *(const int *)arg;
    int square = number * number;

    printf("Square of %d is %d\n", number, square);
    return NULL;
}

int main(void)
{
    const int numbers[] = {1, 2, 3, 4, 5};
    const size_t count = sizeof(numbers) / sizeof(numbers[0]);
    pthread_t threads[sizeof(numbers) / sizeof(numbers[0])];
    size_t created = 0;
    int status = EXIT_SUCCESS;

    for (size_t i = 0; i < count; i++) {
        int error = pthread_create(&threads[i], NULL, print_square, (void *)&numbers[i]);

        if (error != 0) {
            fprintf(stderr, "pthread_create failed: %s\n", strerror(error));
            status = EXIT_FAILURE;
            break;
        }

        created++;
    }

    for (size_t i = 0; i < created; i++) {
        int error = pthread_join(threads[i], NULL);

        if (error != 0) {
            fprintf(stderr, "pthread_join failed: %s\n", strerror(error));
            status = EXIT_FAILURE;
        }
    }

    return status;
}
