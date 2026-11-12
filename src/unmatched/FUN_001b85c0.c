/* The two leading field reads are both volatile so they keep the source order (s2 before s0). */
#include "dw4/reflected.h"
struct Slot { int p[2]; int cnt; int p3; int *items; int p5[2]; int (*cb)(int, int, int); };
struct Y { int p[4]; struct Slot **arr; };
struct X { int p[4]; struct Y *f16; int p2[7]; int f48; int p3[4]; int *f68; };
struct A2 { int p[13]; struct X *f52; };
struct A1 { int p[24]; int f96; };
int igAttrStackManager_MarkStackChanged();
int igTraversal_TraverseChildren();
extern igMetaObject *DAT_0055ec68[4];
extern igMetaObject *DAT_0055ecd8[4];
extern igMetaObject *DAT_0055efe8[4];
int FUN_001b85c0(int arg0, struct A1 *arg1, struct A2 *arg2) {
    int s0; int s3; struct X *s2; int s1; int a1; igMetaObject *v0; struct Slot *sl; int (*cb)(int, int, int);
        s2 = *(struct X * volatile *)&arg2->f52;
    s0 = *(volatile int *)&arg1->f96;
    s3 = igTraversal_TraverseChildren(arg2);
    a1 = 0;
    switch (s0) { case 0: v0 = DAT_0055efe8[0]; break; case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16: v0 = DAT_0055ecd8[0]; a1 = s0 - 9; break; default: a1 = s0 - 1; v0 = DAT_0055ec68[0]; break; }
    s1 = a1 + s2->f68[v0->_id];
    sl = s2->f16->arr[s1];
    { int n = sl->cnt - 1; int *it = sl->items; int v; cb = sl->cb; v = it[n]; if (cb != 0) { cb(v, s2->f48, (int)cb); } }
    sl->cnt = sl->cnt - 1;
    igAttrStackManager_MarkStackChanged(s2, sl, s1);
    if (s3 == 2) {
        return 2;
    }
    return 0;
}
