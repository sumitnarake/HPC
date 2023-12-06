#include<stdio.h>
#include<time.h>

#define n 200

intmain() {
    clock_tstart=clock();
    printf("The size of matrix: %d\n",n);

    intmatrix[n][n];
    intvector[n];
    intresult[n];

    printf("The elements of the matrix:\n");
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            matrix[i][j]=2;
        }
    }

    printf("The elements of the vector:\n");
    for (int i = 0; i<n; i++) {
        vector[i]=1;
    }

    for (int i = 0; i<n; i++) {
        result[i] = 0;
        for (int j = 0; j<n; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    printf("Result vector:\n");
    for (int i = 0; i<n; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    clock_tend=clock();

    doublet=(double)(end-start)/CLOCKS_PER_SEC;

    printf("Size of Vector: %d\n",n);
    printf("Time taken = %f seconds.\n", t);
    return0;
}
