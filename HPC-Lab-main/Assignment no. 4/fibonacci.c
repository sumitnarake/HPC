#include <stdio.h>
#include <omp.h>

long long fib(int n) {
    if (n <= 1) {
        return n;
    } else {
        long long x, y;
        #pragma omp task shared(x)                       //parallel
        x = fib(n - 1);

        #pragma omp task shared(y)
        y = fib(n - 2);

        #pragma omp taskwait
        return x + y;
    }
}


// long int fib(long int n)
// {
//   long int i, j;
//   if (n<2)                                                  seq
//     return n;
//   else
//     {
//        i=fib(n-1);
//        j=fib(n-2);
//        return i+j;
//     }
// }




int main(){
    int n = 10; // Fibonacci number to compute
    long long result;
    double start_time, end_time;

    start_time = omp_get_wtime();

    #pragma omp parallel
    #pragma omp single
    {
        result = fib(n);
    }

    end_time = omp_get_wtime();
    double execution_time = end_time - start_time;

    printf("Fibonacci(%d) = %lld\n", n, result);
    printf("Execution time = %lf seconds", execution_time);

    return 0;
}