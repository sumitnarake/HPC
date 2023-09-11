#include <stdio.h>
#include <omp.h>

#define ARRAY_SIZE 100

int main()
{
    int data[ARRAY_SIZE];
    int result[ARRAY_SIZE];

    // Initialize the data array
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        data[i] = i;
    }

#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

// Perform some computations on a portion of the data array
#pragma omp for nowait
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            result[i] = data[i] * 2 + thread_id;
        }

        // This section will execute concurrently without waiting for other threads
        printf("Thread %d has completed its task.\n", thread_id);

        // Additional work can be done here, independently by each thread
    }

    printf("All threads have completed their task.\n");

    return 0;
}
