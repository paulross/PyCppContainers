//
// Created by Paul Ross on 28/05/2021.
//
#include "PyMemAllocator.h"

void *malloc_vanilla(void *ctx, size_t size) {
    void *ret = malloc(size);
    return ret;
}

void *calloc_vanilla(void *ctx, size_t nelem, size_t size) {
    void *ret = calloc(nelem, size);
    return ret;
}

void* realloc_vanilla(void *ctx, void *ptr, size_t new_size) {
    void *ret = realloc(ptr, new_size);
    return ret;
}

void free_vanilla(void *ctx, void *ptr) {
    free(ptr);
}

static int new_allocator_count[3];

// Fragile, PyMemAllocatorDomain has 3 enums.
static PyMemAllocatorEx mem_alloc_original[3];

void set_mem_alloc(PyMemAllocatorDomain domain, PyMemAllocatorEx *allocator) {
    if (new_allocator_count[domain] == 0) {
        mem_alloc_original[domain] = *allocator;
        ++new_allocator_count[domain];
    }
    PyMem_SetAllocator(domain, allocator);
}

void reset_mem_alloc(PyMemAllocatorDomain domain) {
    if (new_allocator_count[domain] != 0) {
        PyMem_SetAllocator(domain, &mem_alloc_original[domain]);
    }
}

//     PyMemAllocatorEx allocator_mem_new {
//        .ctx=NULL,
//        .malloc=&malloc_new,
//        .calloc=&calloc_new,
//        .realloc=&realloc_new,
//        .free=&free_new
//    };

//{
//PyMemAllocatorEx allocator_raw;
//PyMem_GetAllocator(PYMEM_DOMAIN_RAW, &allocator_raw);
//PyMemAllocatorEx allocator_mem;
//PyMem_GetAllocator(PYMEM_DOMAIN_MEM, &allocator_mem);
//PyMemAllocatorEx allocator_obj;
//PyMem_GetAllocator(PYMEM_DOMAIN_OBJ, &allocator_obj);
//
//PyMemAllocatorEx allocator_mem_new {NULL, &malloc_new, &calloc_new, &realloc_new, &free_new};
//PyMem_SetAllocator(PYMEM_DOMAIN_MEM, &allocator_mem_new);
//PyMem_SetAllocator(PYMEM_DOMAIN_OBJ, &allocator_mem_new);
//
//PyMem_GetAllocator(PYMEM_DOMAIN_MEM, &allocator_mem);
//PyMem_GetAllocator(PYMEM_DOMAIN_OBJ, &allocator_obj);
//
//}
