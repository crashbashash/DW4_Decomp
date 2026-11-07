#include "dw4/reflected.h"
extern "C" {
int igObject_InitHeader(beNDMWMcUtilCtrl *);
int igObject_Destroy(igObject *);
extern int DAT_0053cda0[4];
extern void * DAT_00586dc8[4];
int beNDMWMcUtilCtrl_GetVTable(void);
}
int beNDMWMcUtilCtrl_GetVTable(void) {
    beNDMWMcUtilCtrl obj;
    igObject *o;
    int t;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &DAT_0053cda0[0];
    obj._svData = 0;
    obj._slot = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    *(int **)&obj._vtable = &DAT_0053cda0[0];
    if (&obj._slot != 0) {
        o = (igObject *)obj._slot;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (&obj._svData != 0) {
        o = (igObject *)obj._svData;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}
