#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"
extern "C" {
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
igObject *beBaseInfoDataList_Create(void *);
igObject *igProperty_FindByName(void *, int, char *);
void List_RemoveWordAt(void *, int);
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}

extern "C" void FUN_003a8580(beBaseInfoRam *self, char *name) {
    igTDataList<igObject *> *l1;
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
            igSmartPointer<igObject> h(beBaseInfoDataList_Create(alloc));
            cur = h.p;
            if (cur != 0) cur->_refCount = cur->_refCount + 1;
            old = (igObject *)self->_dataList;
            if (old != 0) { old->_refCount = old->_refCount - 1; if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old); }
            self->_dataList = (int)cur;
        }
        found = igProperty_FindByName((void *)self->_dataList, DAT_00585be0[0], name);
        if (found != 0) {
            l1 = (igTDataList<igObject *> *)self->_dataList;
            idx = l1->find(found);
            l1 = (igTDataList<igObject *> *)self->_dataList;
            obj = l1->_data[idx];
            if (obj != 0) { obj->_refCount = obj->_refCount - 1; if ((obj->_refCount & 0x7fffff) == 0) igObject_Destroy(obj); }
            List_RemoveWordAt(l1, idx);
            l1->_data[l1->_count] = 0;
        }
    }
}
