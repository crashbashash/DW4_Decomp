/* operator new, the catch-type match of the exception handler, the terminate and unexpected handlers, the chain of
 * static objects destroyed at exit and the static initializer run. */
#include "dw4/runtime/exception.h"
#include "dw4/runtime/cxxlib.h"

/* Allocates `size` bytes; while there is no memory it calls the new handler, and with no handler it throws
 * std::bad_alloc or returns null as __throws_bad_alloc says. */
void *operator new(size_t size) throw(std::bad_alloc) {
    void *ptr;

    if (size == 0) size = 1;
    while ((ptr = malloc(size)) == 0) {
        if (std::__new_handler) {
            std::__new_handler();
        } else if (std::__throws_bad_alloc) {
            throw std::bad_alloc();
        } else {
            return 0;
        }
    }
    return ptr;
}

/* Does the thrown type string match the catch type string; the base-class offset of a match goes to *offset_result.
 * A type string is a mangled name; a class with bases is "!class!base!offset!...". */
extern "C" char __throw_catch_compare(const char *throwtype, const char *catchtype, long *offset_result) {
    const char *cptr1, *cptr2;

    *offset_result = 0;
    if ((cptr2 = catchtype) == 0) {
        return true;
    }
    cptr1 = throwtype;

    if (*cptr2 == 'P') {
        cptr2++;
        if (*cptr2 == 'C') cptr2++;
        if (*cptr2 == 'V') cptr2++;
        if (*cptr2 == 'v') {
            if (*cptr1 == 'P' || *cptr1 == '*') {
                return true;
            }
        }
        cptr2 = catchtype;
    }

    switch (*cptr1) {
    case '*':
    case '!':
        if (*cptr1++ != *cptr2++) return false;
        for (;;) {
            if (*cptr1 == *cptr2++) {
                if (*cptr1++ == '!') {
                    long offset;

                    for (offset = 0; *cptr1 != '!';) offset = offset * 10 + *cptr1++ - '0';
                    *offset_result = offset;
                    return true;
                }
            } else {
                while (*cptr1++ != '!') ;
                while (*cptr1++ != '!') ;
                if (*cptr1 == 0) return false;
                cptr2 = catchtype + 1;
            }
        }
        return false;
    }

    while ((*cptr1 == 'P' || *cptr1 == 'R') && *cptr1 == *cptr2) {
        cptr1++;
        cptr2++;

        if (*cptr2 == 'C') {
            if (*cptr1 == 'C') cptr1++;
            cptr2++;
        }
        if (*cptr1 == 'C') return false;

        if (*cptr2 == 'V') {
            if (*cptr1 == 'V') cptr1++;
            cptr2++;
        }
        if (*cptr1 == 'V') return false;
    }

    for (; *cptr1 == *cptr2; cptr1++, cptr2++) if (*cptr1 == 0) return true;
    return false;
}

static void default_unexpected_handler();
static void default_terminate_handler();

static std::terminate_handler thandler = default_terminate_handler;
static std::unexpected_handler uhandler = default_unexpected_handler;

/* A function's exception specification was violated. */
extern "C" void __call_unexpected_handler(void) {
    uhandler();
}

extern "C" void __terminate(void) {
    thandler();
}

static void default_unexpected_handler() {
    thandler();
}

static void default_terminate_handler() {
    abort();
}

/* A static object with a destructor, registered when its constructor has run; the chain runs newest first at exit. */
typedef struct DestructorChain {
    struct DestructorChain *next;
    void (*destructor)(void *object, short flag);
    void *object;
} DestructorChain;

static DestructorChain *__global_destructor_chain;

extern "C" void __destroy_global_chain(void) {
    DestructorChain *link;

    while ((link = __global_destructor_chain) != 0) {
        __global_destructor_chain = link->next;
        link->destructor(link->object, -1);
    }
}

extern "C" void *__register_global_object(void *object, void (*destructor)(void *object, short flag), DestructorChain *link) {
    link->next = __global_destructor_chain;
    link->destructor = destructor;
    link->object = object;
    __global_destructor_chain = link;
    return object;
}

/* Runs the static initializers of the image; the exception index bounds it is also given are found by
 * __GetExceptionIndexBounds instead. */
extern "C" void __call_static_initializers(StaticInitializer *begin, StaticInitializer *end, ExceptionTableIndex *extab_begin, ExceptionTableIndex *extab_end) {
    StaticInitializer *initializer;

    for (initializer = begin; initializer < end; initializer++) {
        (*initializer)();
    }
}
