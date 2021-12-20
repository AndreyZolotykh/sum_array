#include "sum_array.hpp"
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::chrono;

int main() {
    const int array_size = 10'000'000;
    const int number_threads = 4;

    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";

    SumArray sum(array_size, number_threads);

    //calsulate sum using threads
    auto t_start = system_clock::now();
    auto s = sum.calculate_using_threads();
    auto t_end = system_clock::now();
    long diff = duration_cast<milliseconds>(t_end - t_start).count();
    std::cout << "SUM (using threads: " << number_threads << ") is " << s << "  Time (ms): " << diff << std::endl;

    //calculate sum in main thread
    t_start = system_clock::now();
    s = sum.calculate_without_threads();
    t_end = system_clock::now();
    diff = duration_cast<milliseconds>(t_end - t_start).count();
    std::cout << "SUM (main thread) is " << s << "  Time (ms): " << diff << std::endl;

    return 0;
}
