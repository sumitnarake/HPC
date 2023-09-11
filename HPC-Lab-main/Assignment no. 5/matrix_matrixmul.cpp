#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N 3

int main() {
    int A[N][N] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int B[N][N] = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    int result[N][N];

    // Sequential matrix multiplication
    clock_t start_seq = clock();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    clock_t end_seq = clock();

    // Print the result matrix
    printf("Sequential Result Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Calculate sequential execution time
    double seq_time = (double)(end_seq - start_seq) / CLOCKS_PER_SEC;
    printf("Sequential Execution Time: %f seconds\n", seq_time);

    // Parallel matrix multiplication
    double start = omp_get_wtime();
    #pragma omp parallel for shared(A, B, result) collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double end = omp_get_wtime();

    // Print the result matrix
    printf("Parallel Result Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Calculate parallel execution time
    double parallel_time = end - start;
    printf("Parallel Execution Time: %f seconds\n", parallel_time);

    return 0;
}

