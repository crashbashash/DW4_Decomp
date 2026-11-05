#include "dw4/reflected.h"
struct Obj { int *vt; int w1; char *w2; int w3; int w4; igObject *w5; int w6; int w7; };
int igObject_InitHeader(struct Obj *);
int igObject_Destroy();
int StringChunk_ReleaseHeader();
extern int DAT_0052f4a0[4];
extern int DAT_00524950[4];
extern void * DAT_00586dc8[4];
int igMemoryPoolContextInfo_GetVTable(void) {
    struct Obj obj;
    char *o;
    igObject *r;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0052f4a0[0];
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052f4a0[0];
    if (&obj.w5 != 0) {
        r = obj.w5;
        if (r != 0) {
            r->_refCount = r->_refCount - 1;
            if ((r->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(r);
            }
        }
    }
    obj.vt = &DAT_00524950[0];
    if (&obj.w2 != 0) {
        o = obj.w2;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}
