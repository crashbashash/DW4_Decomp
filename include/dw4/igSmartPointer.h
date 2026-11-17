#ifndef DW4_IGSMARTPOINTER_H
#define DW4_IGSMARTPOINTER_H
#include "dw4/reflected.h"
#include "dw4/igObjectDispatchView.h"
#include "dw4/igObject.h"

/* igObject with its vtable as a real vptr, for classes whose virtual functions are called. */
class igVirtualObject {
public:
    virtual void firstSlot();
    unsigned int _refCount;
};

static inline void igObject_Destroy(igVirtualObject *object) { igObject_Destroy((igObject *)object); }

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

static inline void igRelease(igObjectDispatchView *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
    }
}

/* An empty class passed by value writes one byte to the stack; an enum tag writes nothing. */
struct AdoptReference {};
enum RetainReference { kRetainReference };

/* The pointer word an object list copies in on insert, holding the reference the list takes. It is
 * a class member, not a plain pointer local: igDirectory_InsertObject and igIGBFile_ShareEntries store the word and load
 * it back from its stack slot before the null test (`sw v0,104(sp); lw v1,104(sp); beqz v1`), which
 * MWCC emits for a member read after the constructor's store. A scalar local or parameter is tested
 * from the register and stored in the branch delay slot (712 bytes against retail's 716, and 720
 * against 724). */
template <class T> struct RetainedWord {
    T *p;
    RetainedWord(T *object) : p(object) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
};

/* A pointer word handed to a list insert as a temporary argument, which the insert helper retains
 * after it is stored: retail stores the word, then loads the list into the null test's delay slot
 * (`sw v0,124(sp); lw v1,124(sp); beqz v1; lw a0,16(s1)`). RetainedWord, which retains in its
 * constructor, leaves that slot empty (+4 B per insert). */
struct HeldWord {
    igObject *p;
    HeldWord(igObject *object) : p(object) {}
    void retain() const {
        if (p != 0) p->_refCount = p->_refCount + 1;
    }
};

/* A temporary smart pointer (one built in an argument bound to a const reference, or a by-value
 * return used in place) is released with p reloaded from its stack slot after the count store. A
 * named local passed the same way is released from one read. So a caller that shows the reload
 * holds a temporary, not a second class. */
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
