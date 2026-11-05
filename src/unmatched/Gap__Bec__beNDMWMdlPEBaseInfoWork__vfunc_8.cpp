#include "dw4/reflected.h"
/* igObject header: vtable and reference count (the count is not a reflected field) */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
extern int Gap__Core__igObject__vfunc_08__002ff0f0(beNDMWMdlPEBaseInfoWork *);
extern int beMessenger_SendNamed(int, int *, int, int, int *);
extern int igObject_Destroy(igObject *);
extern int DAT_004cfc50[4];
extern int DAT_004cfe70[4];
extern int DAT_004cfe78[4];
extern int DAT_0051d3a8[4];
extern int DAT_0051d3e8[4];
void Gap__Bec__beNDMWMdlPEBaseInfoWork__vfunc_8(beNDMWMdlPEBaseInfoWork *arg0);
void Gap__Bec__beNDMWMdlPEBaseInfoWork__vfunc_8(beNDMWMdlPEBaseInfoWork *arg0) {
//D<
    igIntList *l;
    igIntList *l2;
    int n;
    int n2;
    int *d;
    int *d2;
    int j;
    int j2;
    int i;
    int off;
    int *p;
    igObject *o;
//D>

    if (arg0->_messenger != 0 && arg0->_dispRamNoList != 0) {
        if (arg0->_isPlayer != 0) {
            l = (igIntList *)arg0->_upDataList;
            if (l != 0) {
                n = l->_count;
                d = (int *)l->_data;
                for (j = 0; j < n; j++) d[j] = DAT_004cfe70[0];
            }
            l2 = (igIntList *)arg0->_downDataList;
            if (l2 != 0) {
                n2 = l2->_count;
                d2 = (int *)l2->_data;
                for (j2 = 0; j2 < n2; j2++) d2[j2] = DAT_004cfe78[0];
            }
        }
        i = 0;
        off = 0;
        p = &DAT_004cfc50[0];
        do {
            int v = *(int *)((char *)((igIntList *)arg0->_dispRamNoList)->_data + off);
            if (v != -1) {
                beMessenger_SendNamed(arg0->_messenger, &DAT_0051d3a8[0], *p, v, &DAT_0051d3e8[0]);
            }
            i++;
            off += 4;
            p += 1;
        } while (i < 12);
        o = (igObject *)arg0->_dispRamNoList;
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg0->_dispRamNoList = 0;
        o = (igObject *)arg0->_dispPosNoList;
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg0->_dispPosNoList = 0;
        o = (igObject *)arg0->_timerList;
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg0->_timerList = 0;
        o = (igObject *)arg0->_isFirstList;
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(o);
        }
        arg0->_isFirstList = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
} /* extern "C" */
