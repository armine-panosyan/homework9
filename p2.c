#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const int *numbers;
    int start;
    int end;
    int id;
} ThreadData;

void *sum_half(void *arg)
{
    const ThreadData *data = arg;
    int sum = 0;

    for (int i = data->start; i < data->end; i++) {
        sum += data->numbers[i];
    }

    printf("Thread %d: partial sum = %d\n", data->id, sum);
    return NULL;
}

int main(void)
{
    int numbers[] = {1, 2, 3, 4, 5, 6};
    int length = sizeof(numbers) / sizeof(numbers[0]);
    int middle = length / 2;

    pthread_t threads[2];
    ThreadData parts[2] = {
        {numbers, 0, middle, 1},
        {numbers, middle, length, 2}
    };

    int created = 0;
    int status = EXIT_SUCCESS;

    for (int i = 0; i < 2; i++) {
        int error = pthread_create(&threads[i], NULL, sum_half, &parts[i]);
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
