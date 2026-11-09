#include "dw4/reflected.h"
extern "C" {
igObject *igMetaObject_CreateInstance(int, int);
int igObject_Destroy(igObject *);
}
static inline void releaseObject(igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) igObject_Destroy(object);
    }
}
struct CreatedRef {
    igObject *p;
    CreatedRef(igObject *object) : p(object) {
        if (p != 0) p->_refCount = p->_refCount + 1;
    }
    CreatedRef(const CreatedRef &other) : p(other.p) {
        if (p != 0) p->_refCount = p->_refCount + 1;
    }
    ~CreatedRef() { releaseObject(p); }
    igObject *get() const { return p; }
};
/* The new instance arrives with one reference; the holder takes its own and drops that one. */
extern "C" CreatedRef FUN_002fd6e0(int meta, int pool) {
    CreatedRef created(igMetaObject_CreateInstance(meta, pool));
    releaseObject(created.get());
    return created;
}
