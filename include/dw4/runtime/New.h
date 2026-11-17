/* The Metrowerks runtime's array construction and destruction for new[]/delete[] and array members. */
#ifndef DW4_RUNTIME_NEW_H
#define DW4_RUNTIME_NEW_H

typedef unsigned int size_t;

/* A constructor or destructor as the compiler calls it for an array element: the element and the
 * constructor's "complete object" flag or the destructor's "delete" flag (-1: destroy only). */
typedef void (*ConstructorDestructor)(void *object, short flag);

extern "C" {
void __destroy_arr(void *block, ConstructorDestructor dtor, size_t size, size_t n);
void __construct_array(void *block, ConstructorDestructor ctor, ConstructorDestructor dtor, size_t size, size_t n);
}

#endif
