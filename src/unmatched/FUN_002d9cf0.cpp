#include "dw4/reflected.h"
extern "C" {

void igObject_Destroy(igObject *);
int FUN_001cafc0(igObject *, int *, int);
int FUN_002eb010(int);
int StringChunk_ReleaseHeader(int, int *);
int StringList_CopyRetained(int *, igObject *, int);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
extern int DAT_00586f20[4];
}
template <class T> struct igSmartPointer {
    T *p;
    ~igSmartPointer() { T *o; if ((o = p) != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct Util {
    static inline void assign(igSmartPointer<igObject> &r, igObject *n) {
        igObject *o;
        if (n != 0) ++n->_refCount;
        if ((o = r.p) != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); }
        r.p = n;
    }
    static inline void relstr(int s) {
        if (s != 0) {
            int *h = (int *)(s - 8);
            int c = *(int *)(s - 4) - 1;
            *(int *)(s - 4) = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
        }
    }
};
extern "C" int FUN_002d9cf0(igDriverDatabase *arg0, int arg1, int arg2) {
    igSmartPointer<igObject> sp5C;
    igSmartPointer<igObject> sp58;
    int sp54, sp50;
    igObject *x;
    int idx;
    int v;
    int r;
    sp5C.p = 0;
    sp58.p = 0;
    x = ((igObject **)((igObjectList *)arg0->_subPropertyNames)->_data)[arg1];
    if (x == 0) return 0;
    Util::assign(sp5C, x);
    Util::assign(sp58, ((igObject **)((igObjectList *)arg0->_subPropertyValues)->_data)[arg1]);
    if (arg2 == 0) {
        v = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            int al = FUN_002eb010(16);
            if (al != 0) al = StringPool_Construct(al);
            DAT_00586f20[0] = al;
        }
        v = StringPool_Intern(DAT_00586f20[0], arg2);
    }
    sp54 = v;
    idx = FUN_001cafc0(sp5C.p, &sp54, 0);
    Util::relstr(sp54);
    if (idx >= 0) {
        StringList_CopyRetained(&sp50, sp58.p, idx);
        r = sp50;
        Util::relstr(r);
        return r;
    }
    return 0;
}
