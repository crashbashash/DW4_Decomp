/* The C++ library's side of the Metrowerks runtime: the standard exception classes, the allocation hooks and the
 * terminate/unexpected handlers. */
#ifndef DW4_RUNTIME_CXXLIB_H
#define DW4_RUNTIME_CXXLIB_H

typedef unsigned int size_t;

extern "C" void *malloc(size_t size);
extern "C" void free(void *block);
extern "C" void abort(void);

namespace std {

class exception {
public:
    exception() {}
    virtual ~exception() {}
    virtual const char *what() const { return "exception"; }
};

class bad_alloc : public exception {
public:
    bad_alloc() {}
    virtual ~bad_alloc() {}
    virtual const char *what() const { return "bad_alloc"; }
};

class bad_exception : public exception {
public:
    bad_exception() {}
    virtual ~bad_exception() {}
    virtual const char *what() const { return "bad_exception"; }
};

typedef void (*new_handler)();
typedef void (*terminate_handler)();
typedef void (*unexpected_handler)();

void __default_new_handler() throw(bad_alloc);

/* Called when operator new finds no memory; null makes operator new throw bad_alloc or return 0. */
extern new_handler __new_handler;
/* Whether operator new throws bad_alloc when there is no handler (else it returns 0). */
extern char __throws_bad_alloc;

}

void *operator new(size_t size) throw(std::bad_alloc);
void operator delete(void *block) throw();

#endif
