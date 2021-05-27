#include <iostream>

#include <Python.h>

#include "test_functional.h"
#include "test_performance.h"
#include "test_memory.h"


void test_all() {
    TestResultS test_results;

//    test_functional_all(test_results);
    test_performance_all(test_results);
//    test_memory_all(test_results);

    std::cout << test_results << std::endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    Py_Initialize();

    RSSSnapshot rss_overall("main.cpp");

//    std::cout << "Enter to start... ";
//    std::cout.flush();
//    system("read");

    test_all();

    std::cout << "Count of unique strings: " << count_of_unique_string() << std::endl;

//    std::cout << "Enter to Py_FinalizeEx... ";
//    std::cout.flush();
//    system("read");

    Py_FinalizeEx();

//    std::cout << "Enter to finish... ";
//    std::cout.flush();
//    system("read");

    std::cout << "====" << rss_overall << std::endl;

    std::cout << "Bye, bye!" << std::endl;
    return 0;
}
