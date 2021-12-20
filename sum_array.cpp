#include "sum_array.hpp"
#include <thread>
#include <iostream>
#include <algorithm>    // for for_each()
#include <numeric>      // for accumulate()

SumArray::SumArray(int size_, int num_threads_): size_(size_), num_threads_(num_threads_) {
    const int min_value = 0;
    const int max_value = 10;
    srand(std::time(0));
    for (int i = 0; i < size_; i++) 
        values_.push_back(min_value + rand() % (max_value - min_value + 1));
}

void SumArray::calc_sum_part(int l_index, int r_index) {
    long long sum = 0;
    while (l_index <= r_index) {
        sum += values_[l_index++];
    }
    sum_ += sum;
}

long long SumArray::calculate_without_threads() {
    long long sum = 0;
    for (auto& v : values_) 
        sum += v;

    // std::for_each(values_.begin(),values_.end(), [&sum](int &v){sum +=v;} ); // так тоже можно
    // sum = std::accumulate(values_.begin(),values_.end(), 0);                 // или так

    return sum;
}

long long SumArray::calculate_using_threads() {
    std::vector<std::thread> threads;
    int l_index {};
    int r_index {};
    int elements_count = size_/num_threads_;
    sum_ = 0;

    for (int i = 0; i < num_threads_; i++) {
        if (i == num_threads_ - 1)
            r_index = values_.size();    //if we have left elements, we consider them
        else
            r_index += elements_count;

        //create a thread
        std::thread t(&SumArray::calc_sum_part, this, l_index, r_index - 1);
        threads.push_back(std::move(t));
        l_index += elements_count;
    }

    for (auto& t: threads) 
        if (t.joinable())
            t.join();

    return sum_;
}

void SumArray::print_array() {
    std::cout << "Array:" << std::endl;
    for (auto& v : values_)
        std::cout << v << " ";
    std::cout << "\n" << std::endl;
}
