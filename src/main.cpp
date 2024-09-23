#include <iostream>
#include <iomanip>

#include <Python.h>

#include <cpp/save_stream_state.h>

#include "cpy/tests/test_functional.h"
#include "cpy/tests/test_performance.h"
#include "cpy/tests/test_memory.h"

// Controls execution of test_performance_all() which takes a long time.
#define TEST_PERFORMANCE_ALL 0

void test_all() {
    TestResultS test_results;

    // With debug this take around 130 seconds.
    // With release this takes around 900 seconds.
    test_functional_all(test_results);
#ifdef NDEBUG
#if TEST_PERFORMANCE_ALL
    // These take a long time
    test_performance_all(test_results);
#endif
#endif
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
    {
        StreamFormatState stream_state(std::cout);
        std::cout << std::setprecision(3) << std::fixed;
        std::cout << "Total execution time: " << std::setw(12) << exec_clock.seconds() << " (s)" << std::endl;
    }
    std::cout << "Count of unique strings created: " << count_of_unique_string() << std::endl;
    std::cout << "Bye, bye!" << std::endl;
    return 0;
}
