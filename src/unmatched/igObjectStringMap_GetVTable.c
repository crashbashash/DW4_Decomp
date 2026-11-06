#include "dw4/reflected.h"
int igObject_InitHeader();
int igObject_Destroy();
extern int DAT_00532d80[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[16]; };
int igObjectStringMap_GetVTable(void) {
    union U u;
    int t;
    igObject *o;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;
    int *q8;
    int *q12;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00532d80[0];
    q8 = (int *)&u.b[8];
    *q8 = 0;
    q12 = (int *)&u.b[12];
    *q12 = 0;
    t = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00532d80[0];
    if (q12 != 0) {
        o = (igObject *)*q12;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (q8 != 0) {
        o = (igObject *)*q8;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}
