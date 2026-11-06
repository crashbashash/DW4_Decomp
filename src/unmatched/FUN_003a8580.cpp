#include "dw4/reflected.h"
/* Receiver beBaseInfoRam: _dataList at +40 is a 4-byte handle to an igObjectList of refcounted
 * igProperty records; _data is the igMemoryRef element array. */
/* matching construct: volatile stack slot -- retail keeps the looked-up property in a frame slot (sw 72(sp)) that
 * holds no reference, so it has no cleanup action; the slot is read once, after the empty-list guard, and the read
 * is hoisted out of the search loop (lw 72(sp) before the loop head). */
struct PropSlot { igObject *volatile p; };
struct ListOps {
    static int IndexOf(igObjectList *l, PropSlot &key) {
        int c = l->_count;
        int i = 0;
        if (0 < c) {
            igObject **d = (igObject **)l->_data;
            igObject *x = key.p;
            do {
                if (x == *d) return i;
                i++;
                d++;
            } while (i < c);
        }
        return -1;
    }
};
extern "C" {
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
igObject *beBaseInfoDataList_Create(void *);
void igObject_Destroy(void *);
igObject *igProperty_FindByName(void *, int, char *);
void List_RemoveWordAt(void *, int);
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
struct RP { igObject *p; RP(igObject *x) { p = x; } ~RP() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } };
/* Stack slot that keeps the looked-up property addressable; it holds no reference, so it needs no
 * cleanup. */
extern "C" void FUN_003a8580(beBaseInfoRam *self, char *name) {
    igObjectList *l1;
    int idx;
    igObject *found;
    igObject *obj;
    igObject *cur;
    igObject *old;
    void *alloc;
    if (self->_dataList != 0) {
        if (self->_dataList == 0) {
            alloc = igObject_GetAllocator(self);
            alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            RP h(beBaseInfoDataList_Create(alloc));
            cur = h.p;
            if (cur != 0) cur->_refCount = cur->_refCount + 1;
            old = (igObject *)self->_dataList;
            if (old != 0) { old->_refCount = old->_refCount - 1; if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old); }
            self->_dataList = (int)cur;
        }
        found = igProperty_FindByName((void *)self->_dataList, DAT_00585be0[0], name);
        if (found != 0) {
            l1 = (igObjectList *)self->_dataList;
            PropSlot hp;
            hp.p = found;
            idx = ListOps::IndexOf(l1, hp);
            /* matching construct: volatile read -- retail reloads the list handle after the search (not CSE'd with the first read) */
            l1 = (igObjectList *)*(volatile int *)&self->_dataList;
            obj = ((igObject **)l1->_data)[idx];
            if (obj != 0) { obj->_refCount = obj->_refCount - 1; if ((obj->_refCount & 0x7fffff) == 0) igObject_Destroy(obj); }
            List_RemoveWordAt(l1, idx);
            ((igObject **)l1->_data)[l1->_count] = 0;
        }
    }
}
