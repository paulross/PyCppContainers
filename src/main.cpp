#include <iostream>
#include <iomanip>

#include <Python.h>

#include "cpy/tests/test_functional.h"
#include "cpy/tests/test_performance.h"
#include "cpy/tests/test_memory.h"


void test_all() {
    TestResultS test_results;

//    test_functional_all(test_results);
//    test_performance_all(test_results);
    test_memory_all(test_results);

    std::cout << test_results << std::endl;
}

void explore_hash_reserve() {
    std::cout << "std::unordered_map<long, long>" << std::endl;
    for (int i = 1024; i < 1024 * 1024 * 2; i *= 2) {
        std::unordered_map<long, long> map;
        auto t_now = std::chrono::high_resolution_clock::now();
        map.reserve(i);
        auto t_exec_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - t_now
            ).count();
        std::cout << "Size: " << std::setw(8) << i << " "  << std::setw(8) << t_exec_ns << " (ns)";
        std::cout << ' ';
        for (int j = 0; j < 40 * t_exec_ns / 1000000; ++j) {
            std::cout << '+';
        }
        std::cout << std::endl;
    }
    std::cout << "std::unordered_map<double, double>" << std::endl;
    for (int i = 1024; i < 1024 * 1024 * 2; i *= 2) {
        std::unordered_map<double, double> map;
        auto t_now = std::chrono::high_resolution_clock::now();
        map.reserve(i);
        auto t_exec_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
                std::chrono::high_resolution_clock::now() - t_now
            ).count();
        std::cout << "Size: " << std::setw(8) << i << " "  << std::setw(8) << t_exec_ns << " (ns)";
        std::cout << ' ';
        for (int j = 0; j < 40 * t_exec_ns / 1000000; ++j) {
            std::cout << '+';
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    ExecClock exec_clock;
    Py_Initialize();

    RSSSnapshot rss_overall("main.cpp");

//    explore_hash_reserve();

    test_all();

//    TestResultS test_results;
//    test_functional_all(test_results);
//    test_memory_all(test_results);
//    std::cout << test_results << std::endl;

    Py_FinalizeEx();

    std::cout << "====" << rss_overall << std::endl;
    std::cout << "Total execution time: " << exec_clock.seconds() << " (s)" << std::endl;
    std::cout << "Bye, bye!" << std::endl;
    return 0;
}
