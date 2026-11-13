/* Array construction and destruction for new[]/delete[] and the array members of classes, operator delete,
 * operator new[] and the default new handler. */
#include "dw4/runtime/cxxlib.h"

/* A constructor or destructor as the compiler calls it for an array element: the element and the
 * constructor's "complete object" flag or the destructor's "delete" flag (-1: destroy only). */
typedef void (*ConstructorDestructor)(void *object, short flag);

/* Destroys the elements constructed so far when an element's constructor throws. */
class __partial_array_destructor {
private:
    void *p;
    size_t size;
    size_t n;
    ConstructorDestructor dtor;
public:
    size_t i;
    __partial_array_destructor(void *array, size_t elementsize, size_t nelements, ConstructorDestructor destructor) {
        p = array;
        size = elementsize;
        n = nelements;
        dtor = destructor;
        i = n;
    }
    ~__partial_array_destructor() {
        char *ptr;
        if (i < n && dtor) {
            for (ptr = (char *)p + size * i; i > 0; i--) {
                ptr -= size;
                dtor(ptr, -1);
            }
        }
    }
};

/* Destroys the `n` elements of an array, last first. */
extern "C" void __destroy_arr(void *block, ConstructorDestructor dtor, size_t size, size_t n) {
    char *p;
    for (p = (char *)block + size * n; n > 0; n--) {
        p -= size;
        dtor(p, -1);
    }
}

extern "C" void __construct_array(void *block, ConstructorDestructor ctor, ConstructorDestructor dtor, size_t size, size_t n) {
    __partial_array_destructor pad(block, size, n, dtor);
    char *p;
    for (pad.i = 0, p = (char *)block; pad.i < n; pad.i++, p += size) {
        ctor(p, 1);
    }
}

void operator delete[](void *block) throw() {
    operator delete(block);
}

void operator delete(void *block) throw() {
    free(block);
}

void *operator new[](size_t size) throw(std::bad_alloc) {
    return operator new(size);
}

/* What operator new calls when it finds no memory, unless the program sets another handler. */
void std::__default_new_handler() throw(std::bad_alloc) {
    throw std::bad_alloc();
}
