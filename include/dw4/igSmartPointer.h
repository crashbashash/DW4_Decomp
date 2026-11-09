#ifndef DW4_IGSMARTPOINTER_H
#define DW4_IGSMARTPOINTER_H
#include "dw4/reflected.h"

extern "C" void igObject_Destroy(void *);

/* igObject with its vtable as a real vptr, for classes whose virtual functions are called. */
class igVirtualObject {
public:
    virtual void firstSlot();
    unsigned int _refCount;
};

static inline void igRelease(igObject *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
    }
}

static inline void igRelease(igVirtualObject *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
    }
}

/* An empty class passed by value writes one byte to the stack; an enum tag writes nothing. */
struct AdoptReference {};
enum RetainReference { kRetainReference };

template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer() : p(0) {}
    igSmartPointer(T *object) : p(object) {}
    igSmartPointer(T *object, AdoptReference) : p(object) {}
    igSmartPointer(T *object, RetainReference) : p(object) { retain(); }
    igSmartPointer(const igSmartPointer &other) : p(other.p) { retain(); }
    template <class U> igSmartPointer(const igSmartPointer<U> &other) : p((T *)other.p) { retain(); }
    ~igSmartPointer() { igRelease(p); }
    T *get() const { return p; }
    T *operator->() const { return p; }
    operator T *() const { return p; }
    void retain() const {
        T *o = p;
        if (o != 0) o->_refCount = o->_refCount + 1;
    }
    void release() { igRelease(p); }
    void clear() {
        release();
        p = 0;
    }
    igSmartPointer &operator=(T *next) {
        T *o;
        if (next != 0) next->_refCount = next->_refCount + 1;
        o = p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
        p = next;
        return *this;
    }
    igSmartPointer &operator=(const igSmartPointer &other) {
        T *next = other.p;
        T *o;
        if (next != 0) next->_refCount = next->_refCount + 1;
        o = p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
        p = next;
        return *this;
    }
    template <class U> igSmartPointer &operator=(const igSmartPointer<U> &other) {
        T *next = (T *)other.p;
        T *o;
        if (next != 0) next->_refCount = next->_refCount + 1;
        o = p;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
        p = next;
        return *this;
    }
};
#endif
