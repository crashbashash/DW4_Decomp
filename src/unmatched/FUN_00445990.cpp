#include "dw4/reflected.h"
/* Refreshes the work record's _upDataList for a player entity. A player's list is fetched from the
 * object the messenger returns for the record's id; everyone else gets a fresh seven-entry
 * igIntList filled with the default value, installed through an owning stack reference. */
extern "C" {
igIntList *FUN_002caa70(...);
void *FUN_003a9250(...);
int List_Reserve(...);
int List_Resize(...);
void *Memory_GetAllocatorBySelector(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
void *beMessenger_GetObject(...);
int beMessenger_PopArgContext(...);
int beMessenger_PushArgContext(...);
int beMessenger_SelectGroup(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
extern int DAT_004cfde0[4];
extern int DAT_0051d4b0[4];
extern int DAT_0051d4b8[4];
extern int DAT_0051d4e8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_00445990(beNDMWMdlPEBase *arg0, void *arg1, beNDMWMdlPEBaseInfoWork *arg2);
}
/* Owning stack reference to the freshly created list: constructed from the creating call and released on
 * scope exit once the work record holds its own reference (reference count in the low 23 bits of
 * _refCount).  The out-of-line copy the exception table names is the retail body 0x00150eb0
 * (config/SLUS-20836/unit-objects.json, duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igIntList *p;
    ObjectRef(igIntList *o) : p(o) {}
    ~ObjectRef() { igIntList *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
void FUN_00445990(beNDMWMdlPEBase *arg0, void *arg1, beNDMWMdlPEBaseInfoWork *arg2) {
    void *al;
    int n;
    igIntList *t;
    int *d;
    igIntList *a;
    int i;
    if (arg2->_isPlayer != 0) {
        beMessenger_PushArgContext(arg0->_messenger);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051d4b0[0]);
        beMessenger_AppendInt(arg0->_messenger, *(int *)((char *)arg1 + 8));
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051d4b8[0]);
        t = *(igIntList **)((char *)FUN_003a9250(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051d4e8[0]) + 12);
        if (t != 0) t->_refCount = t->_refCount + 1;
        a = (igIntList *)arg2->_upDataList;
        if (a != 0) {
            a->_refCount = a->_refCount - 1;
            if ((a->_refCount & 0x7FFFFF) == 0) igObject_Destroy(a);
        }
        arg2->_upDataList = (int)t;
        beMessenger_PopArgContext(arg0->_messenger);
        return;
    }
    al = igObject_GetAllocator();
    if (GPR_00554c14 != 0) {
        al = (void *)(int)al;
    } else {
        al = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    ObjectRef created(FUN_002caa70(al));
    a = created.p;
    if (a->_count < 8) List_Reserve(a, 7, 4);
    a = created.p;
    if (a->_capacity >= 7) a->_count = 7; else List_Resize(a, 7, 4);
    a = created.p;
    n = a->_count;
    d = (int *)a->_data;
    for (i = 0; i < n; i++) {
        d[i] = DAT_004cfde0[0];
    }
    a = created.p;
    if (a != 0) a->_refCount = a->_refCount + 1;
    t = (igIntList *)arg2->_upDataList;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if ((t->_refCount & 0x7FFFFF) == 0) igObject_Destroy(t);
    }
    arg2->_upDataList = (int)a;
}
