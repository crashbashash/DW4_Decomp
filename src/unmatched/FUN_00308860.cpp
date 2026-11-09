#include "dw4/igSmartPointer.h"

extern "C" {
void *FUN_002b9350(void *);
void *FUN_002b9500(void *);
void *FUN_002caa70(void *);
int FUN_0030b3c0(void *, int);
void List_Resize(...);
int ObjectList_AppendRetained(...);
void *igObject_GetAllocator(void *);
}
struct Obj : public igObject { };
struct List { int pad0; int pad1; int count; int cap; int *data; };
static inline int countOf(const List *list) { return list->count; }

struct MemberRef {
    Obj *p;
    MemberRef(Obj *object) : p(object) {}
    ~MemberRef() {
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if ((p->_refCount & 0x7FFFFF) == 0) igObject_Destroy(p);
        }
    }
};
struct Self { char pad[44]; Obj *names; List *values; };
static inline void setNames(Self *self, const MemberRef &value) {
    Obj *held = value.p;
    Obj *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = self->names;
    if (old) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    self->names = held;
}
static inline void setValues(Self *self, const MemberRef &value) {
    Obj *held = value.p;
    Obj *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = (Obj *)self->values;
    if (old) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    self->values = (List *)held;
}
extern "C" void FUN_00308860(Self *self, int name, int value) {
    if (self->names == 0) {
        setNames(self, MemberRef((Obj *)FUN_002b9350(igObject_GetAllocator(self))));
        setValues(self, MemberRef((Obj *)FUN_002caa70(igObject_GetAllocator(self))));
    }
    igSmartPointer<Obj> entry((Obj *)FUN_002b9500(igObject_GetAllocator(self)));
    FUN_0030b3c0(entry.p, name);
    ObjectList_AppendRetained(self->names, entry.p);
    List *values = self->values;
    int top = countOf(values);
    if (top < values->cap) {
        values->count = values->count + 1;
    } else {
        List_Resize(values, top + 1, 4);
    }
    values->data[top] = value;
}
