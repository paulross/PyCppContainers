//
// Created by Paul Ross on 28/05/2021.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_PYMEMALLOCATOR_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_PYMEMALLOCATOR_H

#include <stdlib.h>

#include <Python.h>

void set_mem_alloc(PyMemAllocatorDomain domain, PyMemAllocatorEx *allocator);
void reset_mem_alloc(PyMemAllocatorDomain domain);

#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_PYMEMALLOCATOR_H
