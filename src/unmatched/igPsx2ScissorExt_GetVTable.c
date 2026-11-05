#include "dw4/reflected.h"
int igObject_Destroy();
int igObject_InitHeader();
extern int DAT_00525480[4];
extern int DAT_00530a10[4];
extern void * DAT_00586dc8[4];
union U { int vt; char b[48]; };
int igPsx2ScissorExt_GetVTable(void) {
    union U u;
    int temp_s0;
    char *q1;
    char *q2;
    igObject *a;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00530a10[0];
    q1 = &u.b[8];
    *(int *)q1 = 0;
    q2 = &u.b[16];
    *(int *)q2 = 0;
    u.vt = (int)&DAT_00525480[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00530a10[0];
    if (q2 != 0) {
        a = *(igObject **)q2;
        if (a != 0) {
            a->_refCount = (int)((int) ((int)a->_refCount - 1));
            if (((unsigned long long) ((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (q1 != 0) {
        a = *(igObject **)q1;
        if (a != 0) {
            a->_refCount = (int)((int) ((int)a->_refCount - 1));
            if (((unsigned long long) ((long long)(int)a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return temp_s0;
}
