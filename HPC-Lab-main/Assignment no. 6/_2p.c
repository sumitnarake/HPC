#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
if (argc != 3)
{
printf("Usage: %s [num_threads] [matrix_size]\n", argv[0]);
return 1;
}

int num_threads = atoi(argv[1]);
int n = atoi(argv[2]);

omp_set_num_threads(num_threads);

clock_t start = clock();
printf("The size of matrix: %d\n", n);

int matrix[n][n];
int vector[n];
int result[n];

printf("The elements of the matrix:\n");
for (int i = 0; i < n; i++)
{
for (int j = 0; j < n; j++)
{
matrix[i][j] = 2;
}
}

printf("The elements of the vector:\n");
for (int i = 0; i < n; i++)
{
vector[i] = 1;
}

#pragma omp parallel for
for (int i = 0; i < n; i++)
{
result[i] = 0;
for (int j = 0; j < n; j++)
{
result[i] += matrix[i][j] * vector[j];
}
}

// printf("Result vector:\n");
// for (int i = 0; i < n; i++)
// {
// printf("%d ", result[i]);
// }
clock_t end = clock();

double t = (double)(end - start) / CLOCKS_PER_SEC;

printf("Size of Vector: %d\n", n);
printf("Number of threads: %d\n", num_threads);
printf("Time taken = %f seconds.\n", t);
printf("Speedup = %f\n", 0.021 / t);
printf("\n");

return 0;
}


