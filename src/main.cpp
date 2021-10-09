#include <iostream>

#include <Python.h>

#include "cpy/tests/test_functional.h"
#include "cpy/tests/test_performance.h"
#include "cpy/tests/test_memory.h"


void test_all() {
    TestResultS test_results;

//    test_functional_all(test_results);
    test_performance_all(test_results);
//    test_memory_all(test_results);

    std::cout << test_results << std::endl;
}

void *malloc_new(void *ctx, size_t size) {
    void * ret = malloc(size);
    return ret;
}

void *calloc_new(void *ctx, size_t nelem, size_t size) {
    void * ret = calloc(nelem, size);
    return ret;
}

void* realloc_new(void *ctx, void *ptr, size_t new_size) {
    void * ret = realloc(ptr, new_size);
    return ret;
}

void free_new(void *ctx, void *ptr) {
    free(ptr);
}

void explore_memory_allocation_substitution() {
    PyMemAllocatorEx allocator_raw;
    PyMem_GetAllocator(PYMEM_DOMAIN_RAW, &allocator_raw);
    PyMemAllocatorEx allocator_mem;
    PyMem_GetAllocator(PYMEM_DOMAIN_MEM, &allocator_mem);
    PyMemAllocatorEx allocator_obj;
    PyMem_GetAllocator(PYMEM_DOMAIN_OBJ, &allocator_obj);

    PyMemAllocatorEx allocator_mem_new {NULL, &malloc_new, &calloc_new, &realloc_new, &free_new};
//    PyMem_SetAllocator(PYMEM_DOMAIN_MEM, &allocator_mem_new);
//    PyMem_SetAllocator(PYMEM_DOMAIN_OBJ, &allocator_mem_new);

    PyMem_GetAllocator(PYMEM_DOMAIN_MEM, &allocator_mem);
    PyMem_GetAllocator(PYMEM_DOMAIN_OBJ, &allocator_obj);

    PyObject *foo = PyBytes_FromString("Hello world.");
    Py_DECREF(foo);

    std::cout << "Count of unique strings: " << count_of_unique_string() << std::endl;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    ExecClock exec_clock;
    Py_Initialize();

    RSSSnapshot rss_overall("main.cpp");

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
