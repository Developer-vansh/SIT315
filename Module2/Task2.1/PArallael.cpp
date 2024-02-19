#include <iostream>
#include <fstream>
#include <chrono>
#include <pthread.h>
#include <cstdlib>
#include <vector>

using namespace std;

const int N = 100; // N Constant

vector<vector<int>> A(N, vector<int>(N)); // Matrix A
vector<vector<int>> B(N, vector<int>(N)); // Matrix B
vector<vector<int>> C(N, vector<int>(N)); // Result Matrix C

int chunkSize; // Declaring chunkSize variable

void generateRandomMatrix(vector<vector<int>>& matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10; // generate random numbers between 0 and 9
        }
    }
}

//  multiplyMatrix function
void* multiplyMatrix(void *args) {
    long id = (long)args; // Casting void pointer to long
    int start = id * chunkSize;
    int end = (id + 1) * chunkSize;

    // Matrix multiplication algorithm
    for (int i = start; i < end; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    pthread_exit(NULL); // Exiting the thread
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    generateRandomMatrix(A, N);
    generateRandomMatrix(B, N);

    int NUM_THREADS = 0;
    cout << "Enter number of threads: ";
    cin >> NUM_THREADS;
    pthread_t threads[NUM_THREADS];
    chunkSize = N / NUM_THREADS;

    auto start_time = std::chrono::high_resolution_clock::now();

    // Creating threads for parallel matrix multiplication
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, multiplyMatrix, (void*)i);
    }

    // Joining threads
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Writing result to output file
    ofstream outputFile("output.txt");
    if (outputFile.is_open()) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                outputFile << C[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile.close();
    } else {
        cout << "Error in opening File";
    }

    cout << "Execution Time of multiplication: " << duration.count() << " microseconds" << endl;

    return 0;
}


