#include <iostream>

#include <Python.h>

#include "test_functional.h"
#include "test_performance.h"


int main() {
    std::cout << "Hello, World!" << std::endl;
    Py_Initialize();

    TestResultS test_results;

    test_functional_all(test_results);
//    test_performance_all(test_results);

    std::cout << test_results << std::endl;
    return 0;
}
