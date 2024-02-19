#include <chrono> // Including the chrono library for time measurements
#include <cstdlib> // Including the cstdlib library for memory allocation
#include <iostream> // Including the iostream library for input/output operations
#include <time.h> // Including the time.h library for time-related functions
#include <thread> // Including the thread.h library for creating threads
#include <vector> // Including the vector library for using vector stl

using namespace std::chrono; // Using the chrono namespace for time-related functionality
using namespace std; // Using the standard namespace

// Function to generate random numbers and fill the given vector
void randomVector(int vector[], int size) {
    for (int i = 0; i < size; i++) { // Loop to iterate over each element of the vector
        vector[i] = rand() % 100; // Assigning a random number between 0 and 99 to each element
    }
}

// Function to perform vector addition in parallel
void Addition(int* v1, int* v2, int* v3, int start, int end) {
    for (int i = start; i < end; i++) {
        v3[i] = v1[i] + v2[i];
    }
}

int main() {
    // Size of the vectors
    unsigned long size = 100000000; // Defining the size of the vectors as 100,000,000

    // Seed for random number generation
    srand(time(0)); // Setting the seed for the random number generator based on the current time

    int *v1, *v2, *v3; // Declaring pointers for three integer arrays
    auto start = high_resolution_clock::now(); // Recording the current time before the operation begins

    // Memory allocation for vectors
    v1 = (int *)malloc(size * sizeof(int)); // Allocating memory for the first vector
    v2 = (int *)malloc(size * sizeof(int)); // Allocating memory for the second vector
    v3 = (int *)malloc(size * sizeof(int)); // Allocating memory for the result vector

    // Generating random vectors
    randomVector(v1, size); // Filling the first vector with random numbers
    randomVector(v2, size); // Filling the second vector with random numbers
    
    // Total threads
    int total_threads = 10;
    // Create a vector to store thread objects
    vector<thread> threads;
    // Dividing the work among 10 threads and chunkSize menas how many element each thread will process
    int chunkSize = size / total_threads;
    // Create threads
    for (int thread_id = 0; thread_id < total_threads; thread_id++) {
       // Calculate the start and end index for each thread
        int start_index = thread_id * chunkSize;
        int end_index = (thread_id+1)*(chunkSize);
        // If it is the last thread, then the end index will be the size of the vector because the last thread will process the remaining elements
        if(thread_id == total_threads - 1) end_index= size;
        // Create a thread and pass the function and arguments
        threads.emplace_back(Addition, v1, v2, v3, start_index, end_index);
    }
    // Join the threads
    for (auto &t : threads) {
        t.join();
    }

    auto stop = high_resolution_clock::now(); // Recording the current time after the operation completes
    auto duration = duration_cast<microseconds>(stop - start); // Calculating the duration of the operation

    // Outputting the time taken for the addition
    cout << "Time taken by function: " << duration.count() << " microseconds" << endl;

    // Freeing allocated memory
    free(v1); // Freeing memory allocated for the first vector
    free(v2); // Freeing memory allocated for the second vector
    free(v3); // Freeing memory allocated for the result vector

    return 0; // Indicating successful execution of the program
}
