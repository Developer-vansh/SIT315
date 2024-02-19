#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <vector>

using namespace std;

void generateRandomMatrix(vector<vector<int>>& matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = rand() % 10; // generate random numbers between 0 and 9
        }
    }
}

void multiplyMatrix(vector<vector<int>>& A, vector<vector<int>>& B, vector<vector<int>>& C, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            // intializing with 0, may cotain garbage value
            C[i][j] = 0;
            for (int k = 0; k < size; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // Size of matrix
    int N = 0; 
    cout << "Enter size of the matrix: ";
    cin >> N;
    cout << "Doing matrix calculation of size: " << N << "X" << N << endl;
    vector<vector<int>> A(N, vector<int>(N));
    vector<vector<int>> B(N, vector<int>(N));
    vector<vector<int>> C(N, vector<int>(N));

    // Fill the matrix
    srand(time(NULL)); // Seed for random number generation
    generateRandomMatrix(A, N);
    generateRandomMatrix(B, N);
    
    // Start timer 
    auto start_time = std::chrono::high_resolution_clock::now();
    
    // Perform multiplication
    multiplyMatrix(A, B, C, N);
    
    // Stop timer
    auto end_time = std::chrono::high_resolution_clock::now();
    
    // Calculate duration of multiplication
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

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
