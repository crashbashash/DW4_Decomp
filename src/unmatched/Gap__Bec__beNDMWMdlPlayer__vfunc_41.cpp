/* beNDMWMdlPlayer::vfunc_41 (0x003d4240, 316 bytes): per-ram model-player update hook.
 *
 * Make sure the ram has a data list (create one on demand, pooled allocator unless the global
 * selector flag is clear), then, when the named property's work record has its one-shot flag set,
 * clear it and send the named message for this ram. */
#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(...);
int beMessenger_SendNamed(...);
int igObject_GetAllocator(...);
/* Minimal view of the property's work record: only the byte flag at +292 is used here. */
struct PropertyData { char p[292]; unsigned char f292; };
struct PropertyRecord { char p[20]; PropertyData *q; };
PropertyRecord *igProperty_FindByName(...);
extern int DAT_00516110[4];
extern int DAT_00516148[4];
extern int DAT_005164b0[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the freshly created data list: constructed from the object and released
 * on scope exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the
 * exception table names is the retail body 0x0033e9c0 (config/SLUS-20836/unit-objects.json, duplicate
 * __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_41(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1);
void Gap__Bec__beNDMWMdlPlayer__vfunc_41(beNDMWMdlPlayer *arg0, beBaseInfoRam *arg1) {
    igObject *s0;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        igObject *old;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        ObjectRef ref(beBaseInfoDataList_Create(a));
        s0 = ref.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        old = (igObject *)arg1->_dataList;
        if (old != 0) {
            --old->_refCount;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        arg1->_dataList = (int)s0;
    }
    PropertyData *q = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_00516110)->q;
    if (q->f292 != 0) {
        q->f292 = 0;
        beMessenger_SendNamed(arg0->_messenger, DAT_00516148, 0, arg1->_ramNo, DAT_005164b0);
    }
}
