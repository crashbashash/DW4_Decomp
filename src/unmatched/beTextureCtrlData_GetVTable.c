#include "dw4/reflected.h"
int igObject_InitHeader(beTextureCtrlData *);
int igObject_Destroy();
int StringChunk_ReleaseHeader();
extern int DAT_00539560[4];
extern int DAT_00524950[4];
extern void * DAT_00586dc8[4];
int beTextureCtrlData_GetVTable(void) {
    beTextureCtrlData obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader(&obj);
    obj._name = 0;
    *(int **)&obj._vtable = &DAT_00539560[0];
    obj._tex = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    *(int **)&obj._vtable = &DAT_00539560[0];
    if (&obj._tex != 0) {
        o = (char *)obj._tex;
        if (o != 0) {
            ((igObject *)o)->_refCount = ((igObject *)o)->_refCount - 1;
            if ((((igObject *)o)->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    *(int **)&obj._vtable = &DAT_00524950[0];
    if (&obj._name != 0) {
        o = (char *)obj._name;
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
