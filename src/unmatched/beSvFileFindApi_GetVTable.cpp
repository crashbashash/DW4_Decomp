#include "dw4/reflected.h"
union U { beSvFileFindApi o; int w[24]; char b[96]; };
extern "C" {
int igObject_Destroy(igObject *);
int igObject_InitHeader(char *);
extern int DAT_0053bf90[4];
extern int DAT_0053c070[4];
extern void * DAT_00586dc8[4];
int beSvFileFindApi_GetVTable(void);
}
int beSvFileFindApi_GetVTable(void) {
    union U u;
    int temp_s2;
    int *q2;
    int *q1;
    int *q3;
    igObject *a0;

    igObject_InitHeader(u.b);
    q1 = &u.o._imageWork;
    *q1 = 0;
    u.o._vtable = (int)(&DAT_0053c070[0]);
    q2 = &u.o._mountWork;
    *q2 = 0;
    q3 = &u.o._iconWork;
    *q3 = 0;
    u.o._vtable = (int)(&DAT_0053bf90[0]);
    temp_s2 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.o._vtable = (int)(&DAT_0053c070[0]);
    if (q3 != 0) {
        a0 = (igObject *)*q3;
        if (a0 != 0) {
            a0->_refCount = (int)a0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    if (q2 != 0) {
        a0 = (igObject *)*q2;
        if (a0 != 0) {
            a0->_refCount = (int)a0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    if (q1 != 0) {
        a0 = (igObject *)*q1;
        if (a0 != 0) {
            a0->_refCount = (int)a0->_refCount - 1;
            if (((unsigned long long) ((long long)(int)a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    return temp_s2;
}
