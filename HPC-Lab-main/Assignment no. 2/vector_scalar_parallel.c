#include <omp.h>
#include <stdio.h>

int main(){
    int N = 100;
    int A[N];
    double start_time, end_time, exec_time;

    for(int i=0;i<N;i++){
        A[i] = i + 1;
    }

    int scalar = 212354454;

    // Set threads
    omp_set_num_threads(6);

    start_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++){
        A[i] += scalar;
        // printf("Thread: %d Index: %d\n", omp_get_thread_num(),i);
    }
// for(int i=0;i<N;i++){
    //     printf("%d ", A[i]);
    // }

    end_time = omp_get_wtime();
    exec_time = end_time - start_time;
   
    printf("\nExecution time = %f seconds\n", exec_time);

    return 0;
}