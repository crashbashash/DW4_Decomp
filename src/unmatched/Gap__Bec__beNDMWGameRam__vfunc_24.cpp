/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int List_Reserve(int, int, int);
int igObject_Destroy(struct RefCountedHeader *);
/* reference-counted engine object header: refcount word at +4 */
typedef struct RefCountedHeader { int p0; unsigned refs; } RefCountedHeader;
/* object-reference list header: count at +8, capacity at +12, buffer at +16 (list class not recovered) */
typedef struct ObjectRefList { char p[8]; int count; int cap; RefCountedHeader **data; } ObjectRefList;
#include "dw4/reflected.h"
void Gap__Bec__beNDMWGameRam__vfunc_24(beNDMWGameRam *arg0) {
    RefCountedHeader *r;
    ObjectRefList *l;
    int n;
    int i;
    int off;
    int n3;
    int i3;
    RefCountedHeader *r2;
    ObjectRefList *l2;
    int nb;
    int ib;
    int offb;
    int n3b;
    int i3b;
    i = 0;
    l = (ObjectRefList *)arg0->_commonDataList;
    n = l->count;
    if (0 < n) {
        off = 0;
        do {
            r = *(RefCountedHeader **)((char *)l->data + off);
            if (r != 0) {
                r->refs--;
                if (!(r->refs & 0x7fffff)) igObject_Destroy(r);
            }
            i += 1;
            off += 4;
        } while (i < n);
    }
    n3 = l->count;
    for (i3 = 0; i3 < n3; i3++) {
        l->data[i3] = 0;
    }
    l->count = 0;
    if (!(0 < ((ObjectRefList *)arg0->_commonDataList)->count)) List_Reserve(arg0->_commonDataList, 0, 4);
    l2 = (ObjectRefList *)arg0->_playerDataListList;
    nb = l2->count;
    ib = 0;
    if (0 < nb) {
        offb = 0;
        do {
            r2 = *(RefCountedHeader **)((char *)l2->data + offb);
            if (r2 != 0) {
                r2->refs--;
                if (!(r2->refs & 0x7fffff)) igObject_Destroy(r2);
            }
            ib += 1;
            offb += 4;
        } while (ib < nb);
    }
    n3b = l2->count;
    for (i3b = 0; i3b < n3b; i3b++) {
        l2->data[i3b] = 0;
    }
    l2->count = 0;
    if (!(0 < ((ObjectRefList *)arg0->_playerDataListList)->count)) List_Reserve(arg0->_playerDataListList, 0, 4);
}
} /* extern "C" */
