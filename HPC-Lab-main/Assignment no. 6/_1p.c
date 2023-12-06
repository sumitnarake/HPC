#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

void parallelPrefixSum(int arr[], int n)
{
int prefixSum[n];
prefixSum[0] = arr[0];

#pragma omp parallel for schedule(dynamic)
for (int i = 1; i < n; i++)
{
prefixSum[i] = prefixSum[i - 1] + arr[i];
}

// printf("Parallel Prefix Sum Array:\n");
// for (int i = 0; i < n; i++)
// {
// printf("%d ", prefixSum[i]);
// }
// printf("\n");
}

int main(int argc, char *argv[])
{
if (argc != 3)
{
printf("Usage: %s [num_threads] [array_size]\n", argv[0]);
return 1;
}

int num_threads = atoi(argv[1]);
int n = atoi(argv[2]);

omp_set_num_threads(num_threads);

clock_t start = clock();

printf("The number of elements in the array: %d\n", n);

// printf("The elements of the array:\n");
int arr[n];
// for (int i = 0; i < n; i++)
// {
// arr[i] = 10;
// printf("%d ", arr[i]);
// }

parallelPrefixSum(arr, n);

clock_t end = clock();

double t = (double)(end - start) / CLOCKS_PER_SEC;

printf("Size of Vector: %d\n", n);
printf("Number of threads: %d\n", num_threads);
printf("Time taken = %f seconds.\n", t);
printf("Speedup = %f\n", 0.047 / t);
printf("\n");

return 0;
}

