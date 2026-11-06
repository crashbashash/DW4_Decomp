#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(...);
int beMessenger_SendNamed(...);
int beMessenger_SelectReceivers(...);
int beMessenger_AppendMatrix(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBoolCount(...);
int beMessenger_GetBool(...);
int beMessenger_SelectGroup(...);
int beMessenger_AppendInt(...);
int igObject_GetAllocator(...);
struct PropertyData { char p[292]; unsigned char f292; };
struct PropertyRecord { char p[16]; int f16; PropertyData *q; };
PropertyRecord *igProperty_FindByName(...);
extern int DAT_004cc810[4];
extern int DAT_00516110[4];
extern int DAT_00516148[4];
extern int DAT_00516228[4];
extern int DAT_00516248[4];
extern int DAT_00516260[4];
extern int DAT_00516388[4];
extern int DAT_005164b0[4];
extern int DAT_00516528[4];
extern int DAT_00516538[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* matching construct: the inlined refcount release is a static member so the compiler expands it as retail does */
struct ReleaseRefInline { static inline void go(igObject *object) {
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
struct RamInfoArg { char p0[8]; int f8; char p1[28]; igObject *m40; };
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_43(beNDMWMdlPlayer *arg0, RamInfoArg *arg1);
void Gap__Bec__beNDMWMdlPlayer__vfunc_43(beNDMWMdlPlayer *arg0, RamInfoArg *arg1) {
    igObject *s0;
    PropertyRecord *s3;
    PropertyData *q;
    if (arg1->m40 == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        {
            ObjectRef r(beBaseInfoDataList_Create(a));
            s0 = r.p;
            if (s0 != 0) {
                s0->_refCount++;
            }
            ReleaseRefInline::go(arg1->m40);
            arg1->m40 = s0;
        }
    }
    s3 = igProperty_FindByName(arg1->m40, DAT_00585be0[0], DAT_00516110);
    q = s3->q;
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00516228, DAT_00516528, arg1->f8);
    beMessenger_AppendMatrix(arg0->_messenger, s3->f16 + 32);
    beMessenger_AppendString(arg0->_messenger, DAT_004cc810[arg1->f8]);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00516260);
    beMessenger_SendNamed(arg0->_messenger, DAT_00516228, DAT_00516528, arg1->f8, DAT_00516248);
    if (beMessenger_GetBoolCount(arg0->_messenger) != 0 && (beMessenger_GetBool(arg0->_messenger, 0) & 0xff) == 1) {
        beMessenger_SelectGroup(arg0->_messenger, DAT_00516388);
        beMessenger_AppendInt(arg0->_messenger, arg1->f8);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_00516538);
    }
    if (q->f292 != 0) {
        q->f292 = 0;
        beMessenger_SendNamed(arg0->_messenger, DAT_00516148, 0, arg1->f8, DAT_005164b0);
    }
}
