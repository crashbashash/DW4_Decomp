#include "dw4/reflected.h"
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; char *w10; int w11; char *w12; int w13; int w14; int w15; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int igObject_Destroy(igObject *);
extern int DAT_00538e10[4];
extern int DAT_00539e90[4];
extern void * DAT_00586dc8[4];
int beSaveUtilInfoRam_GetVTable(void);
}
int beSaveUtilInfoRam_GetVTable(void) {
    struct Obj obj;
    igObject *o;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    obj.w10 = 0;
    obj.vt = &DAT_00538e10[0];
    obj.w12 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00538e10[0];
    if (&obj.w12 != 0) {
        o = (igObject *)obj.w12;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    obj.vt = &DAT_00539e90[0];
    if (&obj.w10 != 0) {
        o = (igObject *)obj.w10;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}
