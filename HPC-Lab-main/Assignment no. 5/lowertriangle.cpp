#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N 4

int main()
{
    int A[N][N] = {
        {1, 0, 0, 0},
        {2, 3, 0, 0},
        {4, 5, 6, 0},
        {7, 8, 9, 10}};

    int B[N][N] = {
        {11, 0, 0, 0},
        {12, 13, 0, 0},
        {14, 15, 16, 0},
        {17, 18, 19, 20}};

    int result[N][N];

    // Sequential computation of the sum of lower triangular matrices
    clock_t start_seq = clock();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    clock_t end_seq = clock();

    // Print the result matrix
    printf("Sequential Result Matrix:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Calculate sequential execution time
    double seq_time = (double)(end_seq - start_seq) / CLOCKS_PER_SEC;
    printf("Sequential Execution Time: %f seconds\n", seq_time);

    // Parallel computation of the sum of lower triangular matrices
    double start = omp_get_wtime();
#pragma omp parallel for shared(A, B, result) collapse(2)
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    double end = omp_get_wtime();

    // Print the result matrix
    printf("Parallel Result Matrix:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Calculate parallel execution time
    double parallel_time = end - start;
    printf("Parallel Execution Time: %f seconds\n", parallel_time);

    return 0;
}

