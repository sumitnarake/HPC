#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size, n, local_n;
    int* A = NULL;
    int local_sum = 0, total_sum = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 2) {
        fprintf(stderr, "This program requires exactly two processes.\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == 0) {
        printf("Enter the size of the array (even number): ");
        scanf("%d", &n);

        if (n % 2 != 0) {
            fprintf(stderr, "The size of the array must be even.\n");
            MPI_Finalize();
            return 0;
        }

        A = (int*)malloc(sizeof(int) * n);

        for (int i = 0; i < n; i++) {
            A[i] = i + 1;
        }

        // Send the size of the array to P1
        MPI_Send(&n, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (rank == 1) {
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Calculate local_n (size of the subarray)
    local_n = n / 2;

    // Allocate memory for the local subarray
    int* local_A = (int*)malloc(sizeof(int) * local_n);

    // Scatter the data from the master (P0) to the workers (P0 and P1)
    MPI_Scatter(A, local_n, MPI_INT, local_A, local_n, MPI_INT, 0, MPI_COMM_WORLD);

    // Compute the local sum for the subarray
    for (int i = 0; i < local_n; i++) {
        local_sum += local_A[i];
    }

    // Reduce the local sums to get the total sum
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("\nThe sum of all elements in the array is: %d\n", total_sum);
    }

    if (A != NULL) {
        free(A);
    }
    free(local_A);
    MPI_Finalize();

    return 0;
}

