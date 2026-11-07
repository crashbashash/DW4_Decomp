#include "dw4/reflected.h"
struct Obj { int *vt; int w1; char *w2; igObject *w3; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int igObject_Destroy(igObject *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_00536890[4];
extern int DAT_00524950[4];
extern void * DAT_00586dc8[4];
int beLuaData_GetVTable(void);
}
int beLuaData_GetVTable(void) {
    struct Obj obj;
    char *o;
    igObject *io;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00536890[0];
    obj.w3 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00536890[0];
    if (&obj.w3 != 0) {
        io = obj.w3;
        if (io != 0) {
            io->_refCount = io->_refCount - 1;
            if ((io->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(io);
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
