#include "dw4/reflected.h"
extern "C" {
int igObject_InitHeader(beModelCtrlSCEffect *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_0053aef0[4];
extern void * DAT_00586dc8[4];
int beModelCtrlSCEffect_GetVTable(void);
}
int beModelCtrlSCEffect_GetVTable(void) {
    beModelCtrlSCEffect obj;
    char *o;
    int *a1;
    int v0;
    int t;
    int *p0, *p1;

    igObject_InitHeader(&obj);
    p0 = &obj._modelName;
    p1 = &obj._seqName;
    obj._vtable = (int)&DAT_0053aef0[0];
    *p0 = 0;
    *p1 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj._vtable = (int)&DAT_0053aef0[0];
    if (p1 != 0) {
        o = (char *)*p1;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (p0 != 0) {
        o = (char *)*p0;
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
