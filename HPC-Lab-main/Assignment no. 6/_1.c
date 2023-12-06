#include <stdio.h>
#include <stdlib.h> // Include the stdlib.h header for atoi function
#include <time.h>

void prefixSum(int arr[], int n)
{
int prefixSum[n];
prefixSum[0] = arr[0];

for (int i = 1; i < n; i++)
{
prefixSum[i] = prefixSum[i - 1] + arr[i];
}

printf("Prefix Sum Array:\n");
for (int i = 0; i < n; i++)
{
printf("%d ", prefixSum[i]);
}
printf("\n");
}

int main(int argc, char *argv[])
{
if (argc != 2)
{
printf("Usage: %s [array_size]\n", argv[0]);
return 1;
}

int n = atoi(argv[1]);

clock_t start = clock();

printf("The number of elements in the array: %d\n", n);

printf("The elements of the array:\n");
int arr[n];
for (int i = 0; i < n; i++)
{
arr[i] = 10;
printf("%d ", arr[i]);
}

printf("\n");

prefixSum(arr, n);
clock_t end = clock();

printf("Size of Vector: %d\n", n);
printf("Time taken = %f seconds.\n", (double)(end - start) / CLOCKS_PER_SEC);

return 0;
}
