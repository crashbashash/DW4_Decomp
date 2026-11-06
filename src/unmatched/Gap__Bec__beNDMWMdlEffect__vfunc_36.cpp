#include "dw4/reflected.h"
extern "C" {
/* reference-counted engine object header: refcount word at +4 */
void igObject_Destroy(igObject *);
igObject *FUN_00350020(...);
igObject *beBaseInfoDataList_Create(...);
int FUN_00396340(...);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
/* Property record: reference at +20. */
struct PropertyRecordRef { char p[20]; igObject *f20; };
PropertyRecordRef *igProperty_FindByName(...);
extern int DAT_00515db8[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* matching construct: inline static helper reproduces the retail release sequence */
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning stack reference to the freshly created property data list; released at the end of the
 * full expression that stores it (reference count in the low 23 bits of _refCount). */
class ListRef {
public:
    igObject *p;
    ListRef(igObject *o) : p(o) {}
    ~ListRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the effect work object created here; released on scope exit. */
class EffectRef {
public:
    igObject *p;
    EffectRef(igObject *o) : p(o) {}
    ~EffectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct DataList { static inline void store(beBaseInfoRam *ram, const ListRef &list) {
    igObject *created = list.p;
    igObject *old;
    if (created != 0) {
        created->_refCount++;
    }
    old = (igObject *)ram->_dataList;
    if (old) {
        --old->_refCount;
        if (((unsigned long long)(long long)old->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(old);
    }
    ram->_dataList = (int)created;
} };
/* matching construct: opaque receiver; arg0 is only forwarded */
struct EffectReceiverShim { int dummy; };
extern "C" void Gap__Bec__beNDMWMdlEffect__vfunc_36(EffectReceiverShim *arg0, beBaseInfoRam *arg1);
void Gap__Bec__beNDMWMdlEffect__vfunc_36(EffectReceiverShim *arg0, beBaseInfoRam *arg1) {
    igObject *s0;
    PropertyRecordRef *s1;
    int alloc;
    int a;
    if (arg1->_dataList == 0) {
        alloc = igObject_GetAllocator(arg1);
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        DataList::store(arg1, ListRef(beBaseInfoDataList_Create(a)));
    }
    s1 = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_00515db8);
    alloc = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    /* matching construct: the effect holder is a named local and the list holder above an unnamed
     * temporary; named locals take their frame slots before temporaries (effect +0x5c, list +0x58) */
    EffectRef effect(FUN_00350020(a));
    s0 = effect.p;
    if (s0 != 0) {
        s0->_refCount++;
    }
    ReleaseRef::go(s1->f20);
    s1->f20 = s0;
    FUN_00396340(arg0, arg1);
}
