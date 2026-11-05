#include "dw4/reflected.h"
int igObject_Destroy();
int igMatrix44f_SetIdentity();
int igObject_InitHeader(igMousePosObserver *);
extern int DAT_00541090[4];
extern int D_00541090[4];
extern void * DAT_00586dc8[4];
int igMousePosObserver_GetVTable(void) {
    igMousePosObserver s; igMousePosObserver *o = &s; igObject *a; int t; int *p2; int *p1; int *p0;
    igObject_InitHeader(o);
    o->_vtable = (int)&DAT_00541090[0];
    p0 = &o->_intersectTraversal; p1 = &o->_ray; p2 = &o->_hitPath;
    *p0 = 0; *p1 = 0; *p2 = 0;
    igMatrix44f_SetIdentity(o->_inverseProjectionMatrix);
    t = *(int *)((char *)o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o->_vtable = (int)&D_00541090[0];
    if (p2 != 0) {
        a = *(igObject **)p2;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (p1 != 0) {
        a = *(igObject **)p1;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    if (p0 != 0) {
        a = *(igObject **)p0;
        if (a != 0) {
            *(int *)&a->_refCount = (int)((int) (*(int *)&a->_refCount - 1));
            if (((unsigned long long) ((long long) *(int *)&a->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(a);
            }
        }
    }
    return t;
}
