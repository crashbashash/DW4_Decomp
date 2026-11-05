#include "dw4/reflected.h"
/* reference-counted engine object header: refcount word at +4 (low 23 bits are the count) */
extern "C" {
void igObject_Destroy(igObject *);
}
/* matching construct: inline static helper reproduces the retail release sequence */
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Bec__beNDMWPanelObjectWaza__vfunc_16(beNDMWPanelObjectWaza *arg0);
void Gap__Bec__beNDMWPanelObjectWaza__vfunc_16(beNDMWPanelObjectWaza *arg0) {
    igObjectList *l;
    ReleaseRef::go((igObject *)arg0->_playerDataList);
    arg0->_playerDataList = 0;
    l = (igObjectList *)arg0->_listFolder;
    int n = l->_count;
    int i = 0;
    int off;
    int j;
    if (0 < n) {
        off = 0;
        do {
            ReleaseRef::go(*(igObject **)((char *)l->_data + off));
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
                *(int *)((char *)l->_data + off3) = 0;
                *(int *)((char *)l->_data + off3 + 4) = 0;
                *(int *)((char *)l->_data + off3 + 8) = 0;
                *(int *)((char *)l->_data + off3 + 12) = 0;
                *(int *)((char *)l->_data + off3 + 16) = 0;
                *(int *)((char *)l->_data + off3 + 20) = 0;
                *(int *)((char *)l->_data + off3 + 24) = 0;
                *(int *)((char *)l->_data + off3 + 28) = 0;
                off3 += 32;
            } while (v < lim);
        }
        off4 = v * 4;
        if (v < n2) {
            do {
                v++;
                *(int *)((char *)l->_data + off4) = 0;
                off4 += 4;
            } while (v < n2);
        }
    }
    l->_count = 0;
    ((igObjectList *)arg0->_listColor)->_count = 0;
}
