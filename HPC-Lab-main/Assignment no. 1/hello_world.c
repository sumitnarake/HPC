#include <omp.h>
#include <stdio.h>
#include <pthread.h>

void main()
{
    printf("Hello World\n");
    int n=10;
    omp_set_num_threads(n);
    #pragma omp parallel
    {
        printf("Hello from thread number %d\n", omp_get_thread_num());
    }
}
