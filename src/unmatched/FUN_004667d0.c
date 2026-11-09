#include "dw4/reflected.h"
int FUN_00191f30();
int FUN_004569c0();
int FUN_00456a60();
int List_Resize();
int ObjectList_AppendRetained();
int igObject_Destroy();
int FUN_004665e0();
igProbe *FUN_0019e680();
void FUN_004667d0(igPickMode *arg0) {
    struct { int pad; char b; int w; } sp;
    igProbe * volatile sp4C;
    igProbe *q2;
    igProbe *q;
    igIntList *l;
    int n;
    igIntersectTraversal *m;
    igObject *old;
    igObject *r;
    igProbe *t;
    igIntersectTraversal *m2;
    FUN_00191f30(&sp.w, arg0->_inverseProjectionMatrix, arg0->_parameters + 0x2C);
    sp.b = 0;
    sp4C = FUN_0019e680(0);
    q = sp4C;
    ObjectList_AppendRetained(q->_rays, arg0->_ray);
    l = (igIntList *)q->_intersectFaceType;
    n = *(volatile int *)&l->_count;
    if (n < l->_capacity) {
        l->_count = l->_count + 1;
    } else {
        List_Resize(l, n + 1, 4);
    }
    ((int *)l->_data)[n] = 2;
    q2 = sp4C;
    m = (igIntersectTraversal *)arg0->_intersectTraversal;
    if (q2 != 0) {
        q2->_refCount = q2->_refCount + 1;
    }
    old = (igObject *)m->_probe;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    m->_probe = (int)q2;
    ((igIntersectTraversal *)arg0->_intersectTraversal)->_mode = 0;
    m2 = (igIntersectTraversal *)arg0->_intersectTraversal;
    m2->_mode = m2->_mode | 4;
    ((igIntersectTraversal *)arg0->_intersectTraversal)->_hitProc = (int)&FUN_004665e0;
    ((igIntersectTraversal *)arg0->_intersectTraversal)->_userTimeState = 1;
    if (arg0->_guiSystem != 0) {
        r = (igObject *)((igGuiSystem *)arg0->_guiSystem)->_mouseCursor;
        if (r != 0) {
            r->_refCount = r->_refCount + 1;
        }
        old = (igObject *)arg0->_savedCursor;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(old);
            }
        }
        arg0->_savedCursor = (int)r;
        arg0->_savedCursorState = ((igGuiSystem *)arg0->_guiSystem)->_mouseCursorVisible;
        FUN_00456a60(arg0->_guiSystem, arg0->_cursor);
        FUN_004569c0(arg0->_guiSystem, 1);
    }
    t = sp4C;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if ((t->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
}
