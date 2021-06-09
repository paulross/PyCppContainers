//
// Created by Paul Ross on 28/05/2021.
//

#ifndef PYTHONCPPHOMOGENEOUSCONTAINERS_PYMEMALLOCATOR_H
#define PYTHONCPPHOMOGENEOUSCONTAINERS_PYMEMALLOCATOR_H

#include <Python.h>
#include <stdlib.h>
#include <unordered_map>
#include <list>
#include <string>


class MemoryAllocationTracker {
public:
    void record_malloc(void *ptr, size_t size) {
        if (m_memory_block_map.count(ptr) != 0) {
            m_messages.emplace_back("malloc() returned an already allocated pointer.")
        }
        m_memory_block_map[ptr] = size;
    }
    // TODO: calloc, realloc.
    void record_free(void *ptr) {
        if (m_memory_block_map.count(ptr) == 0) {
            m_messages.emplace_back("free() of not allocated pointer.")
        } else {
            m_memory_block_map.erase(ptr);
        }
    }
protected:
    std::unordered_map<void *, size_t> m_memory_block_map;
    std::list<std::string> m_messages;
};


void set_mem_alloc(PyMemAllocatorDomain domain, PyMemAllocatorEx *allocator);
void reset_mem_alloc(PyMemAllocatorDomain domain);

#endif //PYTHONCPPHOMOGENEOUSCONTAINERS_PYMEMALLOCATOR_H
