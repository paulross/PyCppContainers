#include <iostream>

#include <Python.h>

#include "test_functional.h"
#include "test_performance.h"


void test_all() {
    TestResultS test_results;

//    test_functional_all(test_results);
    test_performance_all(test_results);

    std::cout << test_results << std::endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    Py_Initialize();

    std::cout << "Enter to start... ";
    std::cout.flush();
    system("read");

    test_all();

    std::cout << "Enter to finish... ";
    std::cout.flush();
    system("read");
    std::cout << "Bye, bye!" << std::endl;
    return 0;
}
