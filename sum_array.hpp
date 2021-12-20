#pragma once

#include <vector>

class SumArray {
    int size_ {};                   // size of vector
    int num_threads_ {1};           // number of threads to calculate sum
    std::vector<int>values_;        // vector of values
    long long sum_ {};              // sum of all values of vector
    void calc_sum_part(int l_index, int r_index);   // calculate a sum of values of the interval [l_index, r_index]
public:
    SumArray(int size, int num_threads);            // size_ - size of vector, num_threads_ - number of threads
    ~SumArray() = default;
    long long calculate_using_threads();            // calculate sum of values using threads
    long long calculate_without_threads();          // calculate sum of values in main thread
    void print_array();                              // print values of the vector's elements
};
