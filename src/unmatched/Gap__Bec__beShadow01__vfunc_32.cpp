#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int List_Reserve(...);
}
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beShadow01__vfunc_32(beShadow01 *arg0);
void Gap__Bec__beShadow01__vfunc_32(beShadow01 *arg0) {
    /* matching construct: the int-indexed ((int *)...)[0] stores below spell the raw word stores of retail; they are list-backing-store writes, not game logic. */
    igDataList *l = (igDataList *)arg0->_svInfoList;
    int n = l->_count;
    int i = 0;
    int off;
    int j;
    if (0 < n) {
        off = 0;
        do {
            ReleaseRef::go(((igObject **)((char *)l->_data + off))[0]);
            i++;
            off += 4;
        } while (i < n);
    }
    int n2 = l->_count;
    int v = 0;
    if (0 < n2) {
        int lim;
        int off3;
        int off4;
        if (n2 > 8) {
            lim = n2 - 8;
            off3 = 0;
            do {
                v += 8;
                ((int *)((char *)l->_data + off3))[0] = 0;
                ((int *)((char *)l->_data + off3 + 4))[0] = 0;
                ((int *)((char *)l->_data + off3 + 8))[0] = 0;
                ((int *)((char *)l->_data + off3 + 12))[0] = 0;
                ((int *)((char *)l->_data + off3 + 16))[0] = 0;
                ((int *)((char *)l->_data + off3 + 20))[0] = 0;
                ((int *)((char *)l->_data + off3 + 24))[0] = 0;
                ((int *)((char *)l->_data + off3 + 28))[0] = 0;
                off3 += 32;
            } while (v < lim);
        }
        off4 = v * 4;
        if (v < n2) {
            do {
                v++;
                ((int *)((char *)l->_data + off4))[0] = 0;
                off4 += 4;
            } while (v < n2);
        }
    }
    l->_count = 0;
    if (!(0 < ((igDataList *)arg0->_svInfoList)->_count)) {
        List_Reserve((igDataList *)arg0->_svInfoList, 0, 4);
    }
    arg0->_savePos[0] = 0.0f;
    arg0->_savePos[1] = 0.0f;
    arg0->_savePos[2] = 0.0f;
}
