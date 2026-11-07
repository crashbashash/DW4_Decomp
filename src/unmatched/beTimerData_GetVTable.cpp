#include "dw4/reflected.h"
extern "C" {
int igObject_InitHeader(beTimerData *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_00539700[4];
extern void * DAT_00586dc8[4];
int beTimerData_GetVTable(void);
}
int beTimerData_GetVTable(void) {
    beTimerData obj;
    int *q1;
    int *q2;
    char *o;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    q1 = &obj._resetCondition;
    q2 = &obj._callLuaFile;
    obj._vtable = (int)&DAT_00539700[0];
    obj._resetCondition = 0;
    obj._callLuaFile = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj._vtable = (int)&DAT_00539700[0];
    if (q2 != 0) {
        o = (char *)*q2;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (q1 != 0) {
        o = (char *)*q1;
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
