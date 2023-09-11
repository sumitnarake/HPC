#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>
#include <cstdlib>

using namespace std;

// Function to initialize a matrix with random values
void initializeMatrix(vector<vector<int>>& matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 100;  // Filling with random values between 0 and 99
        }
    }
}

// Function to add two matrices
void addMatrices(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

int main() {
    srand(time(0));  // Seed the random number generator
    
    const int sizes[] = {250, 500, 750, 1000, 2000};
    const int numThreads[] = {1, 2, 4, 8};  // Change the number of threads

    for (int sizeIndex = 0; sizeIndex < 5; sizeIndex++) {
        int size = sizes[sizeIndex];
        vector<vector<int>> A(size, vector<int>(size));
        vector<vector<int>> B(size, vector<int>(size));
        vector<vector<int>> C(size, vector<int>(size));

        initializeMatrix(A, size);
        initializeMatrix(B, size);

        cout << "Matrix Size: " << size << "x" << size << endl;

        for (int numThreadIndex = 0; numThreadIndex < 4; numThreadIndex++) {
            int numThread = numThreads[numThreadIndex];
            omp_set_num_threads(numThread);

            double start_time = omp_get_wtime();

            addMatrices(A, B, C, size);

            double end_time = omp_get_wtime();
            double execution_time = end_time - start_time;

            cout << "Threads: " << numThread << ", Time = " << execution_time << " seconds" << endl;
        }
        cout << endl;
    }

    return 0;
}
