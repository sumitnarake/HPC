#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    const int size = 200;
    vector<int> a(size), b(size), c(size);

    // Initialize vectors 'a' and 'b'

    int chunk_sizes[] = {1, 2, 4, 8, 16}; // Vary the chunk sizes

    for (int chunk_size : chunk_sizes) {
        double start_time = omp_get_wtime();
        
        #pragma omp parallel for schedule(static, chunk_size)
        for (int i = 0; i < size; i++) {
            c[i] = a[i] + b[i];
        }

        double end_time = omp_get_wtime();
        double execution_time = end_time - start_time;

        cout << "Chunk Size " << chunk_size << ": Time = " << execution_time << " seconds" << endl;
    }

    return 0;
}

