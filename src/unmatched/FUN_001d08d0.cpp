#include "dw4/reflected.h"
extern "C" {
void *FUN_002c9740(void *);
void *FUN_002c99b0(void *);
void List_Resize(...);
int igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
extern float DAT_0048da38[4];
extern float DAT_0048da40[4];
extern unsigned char GPR_00554988;
}
struct Src { char pad[20]; int f20; };
struct Self { char pad[44]; Src *f44; igFloatList *f48; igFloatList *f52; igUnsignedCharList *f56; };
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(T *object) : p(object) {}
    ~igSmartPointer() {
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if ((p->_refCount & 0x7FFFFF) == 0) igObject_Destroy(p);
        }
    }
};
struct ByteListRef {
    igUnsignedCharList *p;
    ByteListRef(igUnsignedCharList *object) : p(object) {}
    ~ByteListRef() {
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if ((p->_refCount & 0x7FFFFF) == 0) igObject_Destroy(p);
        }
    }
};
static inline void setFloats(igFloatList *&field, const igSmartPointer<igFloatList> &value) {
    igFloatList *held = value.p;
    igFloatList *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = field;
    if (old) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    field = held;
}
static inline void setBytes(igUnsignedCharList *&field, const ByteListRef &value) {
    igUnsignedCharList *held = value.p;
    igUnsignedCharList *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = field;
    if (old) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    field = held;
}
extern "C" bool FUN_001d08d0(Self *arg0, int arg1) {
    bool r = false;
    int n;
    int i;
    int j;
    if (arg0->f48 == 0) {
        n = arg0->f44->f20;
        {
            igSmartPointer<igFloatList> first((igFloatList *)FUN_002c9740(igObject_GetAllocator(arg0)));
            setFloats(arg0->f48, first);
        }
        {
            igSmartPointer<igFloatList> second((igFloatList *)FUN_002c9740(igObject_GetAllocator(arg0)));
            setFloats(arg0->f52, second);
        }
        {
            ByteListRef flags((igUnsignedCharList *)FUN_002c99b0(igObject_GetAllocator(arg0)));
            setBytes(arg0->f56, flags);
        }
        { igFloatList *l = arg0->f48; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize(l, n, 4); } }
        { igFloatList *l = arg0->f52; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize(l, n, 4); } }
        { igUnsignedCharList *l = arg0->f56; if (n >= 0) { if (n <= l->_capacity) l->_count = n; else List_Resize(l, n, 1); } }
        for (i = 0; i < n; i++) {
            igFloatList *a = arg0->f48;
            int c = a->_count;
            if (c != 0 && i >= 0 && i < c) ((float *)a->_data)[i] = DAT_0048da38[0];
            igFloatList *b = arg0->f52;
            c = b->_count;
            if (c != 0 && i >= 0 && i < c) ((float *)b->_data)[i] = DAT_0048da40[0];
            igUnsignedCharList *d = arg0->f56;
            c = d->_count;
            if (c != 0 && i >= 0 && i < c) ((unsigned char *)d->_data)[i] = GPR_00554988;
        }
    }
    for (j = 0; j < arg1; j++) {
        if (((float *)arg0->f52->_data)[j] != ((float *)arg0->f48->_data)[j]) { r = true; break; }
    }
    return r;
}
