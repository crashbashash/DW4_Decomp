#include "dw4/reflected.h"
extern "C" {
int igObject_Destroy(...);
beDataObjBoolList *igProperty_GetRecordArray(...);
int FUN_003a9250(...);
int igObject_GetAllocator(...);
int Memory_GetAllocatorBySelector(...);
igObject *FUN_003c99a0(...);
int FUN_004435c0(...);
int List_InsertWords(...);
int ObjectList_AppendRetained(...);
extern unsigned char GPR_00554c14;
extern int DAT_0051d1e8[4];
extern int DAT_0051d1f8[4];
extern int DAT_00587110[4];
void FUN_004432a0(beNDMWShinkaCtrl *self);
}
/* Owning stack reference to the evolution entry under construction; released on scope exit
 * (reference count in the low 23 bits of _refCount). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

#pragma opt_loop_invariants off
void FUN_004432a0(beNDMWShinkaCtrl *self) {
    int ia;
    igObject *obj;
    igObjectList *l4;
    igObject *o3;
    igBoolList *s2;
    igObjectList *lst;
    int n;
    int i;
    int cnt;
    int j;
    int idx;
    int base;
    int alloc;

    lst = (igObjectList *)self->_list;
    n = lst->_count;
    for (i = 0; i < n; i++) {
        obj = ((igObject **)lst->_data)[i];
        if (obj != 0) {
            obj->_refCount = obj->_refCount - 1;
            if ((obj->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(obj);
            }
        }
    }
    cnt = lst->_count;
    for (j = 0; j < cnt; j++) {
        ((igObject **)lst->_data)[j] = 0;
    }
    lst->_count = 0;
    s2 = (igBoolList *)igProperty_GetRecordArray(self->_playerParameter, &DAT_0051d1e8[0])->_data;
    FUN_003a9250(self->_playerParameter, &DAT_0051d1f8[0]);
    for (idx = 0; idx < 16; idx++) {
        if ((*(unsigned char **)&s2->_data)[idx] != 0) {
            base = igObject_GetAllocator(self);
            if (GPR_00554c14 != 0) {
                alloc = base;
            } else {
                alloc = Memory_GetAllocatorBySelector(DAT_00587110[0]);
            }
            ObjectRef entry(FUN_003c99a0(alloc));
            igObject *slotB;
            FUN_004435c0(entry.p, self->_gameRam, self->_playerNo, idx);
            if (idx == 3) {
                l4 = (igObjectList *)self->_list;
                o3 = (igObject *)((int)&slotB + 0); /* matching construct: the retained word is re-read through its address */
                slotB = entry.p;
                o3 = *(igObject **)o3;
                if (o3 != 0) {
                    o3->_refCount = o3->_refCount + 1;
                }
                List_InsertWords(l4, 0, 1, &slotB);
            } else {
                ObjectList_AppendRetained((igObjectList *)self->_list, entry.p);
            }
        }
    }
}
#pragma opt_loop_invariants reset
