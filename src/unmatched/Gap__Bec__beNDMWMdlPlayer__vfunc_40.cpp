/* 0x003d40f0 - beNDMWMdlPlayer vfunc 40: creates the ram object's data list on first use (held in an ObjectRef whose
 * destructor the exception table names), then consumes a one-shot flag in the player payload by sending a named
 * message. */
#include "dw4/reflected.h"
extern "C" {
int Memory_GetAllocatorBySelector(int);
int beMessenger_SendNamed(int, int *, int, int, int *);
void igObject_Destroy(igObject *);
int igObject_GetAllocator(void *);
extern int DAT_00516110[4];
extern int DAT_00516148[4];
extern int DAT_005164b0[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
struct PropertyRecord { char pad[20]; int f20; };
struct PropertyPayload { char pad[292]; unsigned char f292; };
struct UnidentifiedArg1Object { char pad[8]; int f8; char pad2[28]; igObject *f40; };
igObject *beBaseInfoDataList_Create(int);
struct PropertyRecord *igProperty_FindByName(igObject *, int, int *);
}
/* Owning stack reference to the freshly created data list: constructed from the object and released on scope
 * exit (reference count in the low 23 bits of _refCount).  The out-of-line copy the exception table names is the
 * retail body 0x0033e9c0 (config/SLUS-20836/unit-objects.json, duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void Gap__Bec__beNDMWMdlPlayer__vfunc_40(beNDMWMdlPlayer *arg0, struct UnidentifiedArg1Object *arg1) {
    struct PropertyPayload *q;

    if (arg1->f40 == 0) {
        int al = igObject_GetAllocator(arg1);
        ObjectRef created(beBaseInfoDataList_Create(GPR_00554c14 != 0 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        igObject *t = created.p;
        if (t != 0) {
            t->_refCount = t->_refCount + 1;
        }
        igObject *u = arg1->f40;
        if (u != 0) {
            u->_refCount = u->_refCount - 1;
            if ((u->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(u);
            }
        }
        arg1->f40 = t;
    }
    q = (struct PropertyPayload *)igProperty_FindByName(arg1->f40, DAT_00585be0[0], &DAT_00516110[0])->f20;
    if (q->f292 != 0) {
        q->f292 = 0U;
        beMessenger_SendNamed(arg0->_messenger, &DAT_00516148[0], 0, arg1->f8, &DAT_005164b0[0]);
    }
}
