#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *FUN_00350020(...);
igObject *beBaseInfoDataList_Create(...);
int FUN_00396340(...);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
struct PropertyRecord { char header[20]; igObject *value; };
PropertyRecord *igProperty_FindByName(...);
extern int DAT_00515d40[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* matching construct: inline release helper reproduces the retail release sequence */
struct ReleaseRef { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the new property value object; released on scope exit. */
class ValueRef {
public:
    igObject *p;
    ValueRef(igObject *o) : p(o) {}
    ~ValueRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Inlined helper shared by the model-controller "apply ram" methods: a ram without a data list gets a
 * fresh beBaseInfoDataList (allocator chosen by the global selector flag).  Being an inlined callee, its
 * list reference is laid out after the caller's own value reference (+0x58 below +0x5c), as retail does.
 * matching construct: inline_depth(2) lets the list reference's destructor inline inside the inlined
 * helper (the default depth leaves an out-of-line call to __dt__9ObjectRefFv). */
struct RamDataList { static inline void Ensure(beBaseInfoRam *ram) {
    igObject *s0;
    if (ram->_dataList == 0) {
        int alloc = igObject_GetAllocator(ram);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        ObjectRef list(beBaseInfoDataList_Create(a));
        s0 = list.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        ReleaseRef::go((igObject *)ram->_dataList);
        ram->_dataList = (int)s0;
    }
} };
extern "C" void Gap__Bec__beNDMWMdlEBullet__vfunc_36(beNDMWMdlEBullet *arg0, beBaseInfoRam *arg1);
void Gap__Bec__beNDMWMdlEBullet__vfunc_36(beNDMWMdlEBullet *arg0, beBaseInfoRam *arg1) {
    igObject *s0;
    PropertyRecord *s1;
    int alloc;
    int a;
    RamDataList::Ensure(arg1);
    s1 = igProperty_FindByName((void *)arg1->_dataList, DAT_00585be0[0], DAT_00515d40);
    alloc = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    ValueRef value(FUN_00350020(a));
    s0 = value.p;
    if (s0 != 0) {
        s0->_refCount++;
    }
    ReleaseRef::go(s1->value);
    s1->value = s0;
    FUN_00396340(arg0, arg1);
}
