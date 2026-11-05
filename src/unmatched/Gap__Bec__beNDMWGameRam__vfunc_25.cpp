#include "dw4/reflected.h"
/* Create the single game-ram info and its ram object when the info list is empty: the two stack
 * holders release the creating shares once both objects are registered (the lists keep their own).
 * The retail unit was C++ (it keeps an exception table for the two holders); the code keeps C
 * linkage. */
extern "C" {
beNDMWGameRamInfo *FUN_003ca380(int);
beNDMWGameRamInfoRam *FUN_003ca1a0(int);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(unsigned, void *);
int beMessenger_RegisterReceiverFromInfo(int, beNDMWGameRamInfoRam *, int *);
int igNamedObject_SetName(beNDMWGameRamInfo *, int *);
void igObject_Destroy(void *);
int igObject_GetAllocator(beNDMWGameRam *);
extern int DAT_00518bb8[4];
extern int DAT_00518bc0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int Gap__Bec__beNDMWGameRam__vfunc_25(beNDMWGameRam *arg0);
}
/* Owning stack reference to the game-ram info created here: released on scope exit (reference count
 * in the low 23 bits of _refCount).  The out-of-line copy the exception table names is the retail
 * body 0x003f8050 (config/SLUS-20836/unit-objects.json, duplicate __dt__7InfoRefFv). */
class InfoRef {
public:
    beNDMWGameRamInfo *p;
    InfoRef(beNDMWGameRamInfo *o) : p(o) {}
    ~InfoRef() { beNDMWGameRamInfo *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the info's ram object created here: released on scope exit.  The
 * out-of-line copy the exception table names is the retail body 0x003f7fd0 (config/SLUS-20836/unit-objects.json,
 * duplicate __dt__6RamRefFv). */
class RamRef {
public:
    beNDMWGameRamInfoRam *p;
    RamRef(beNDMWGameRamInfoRam *o) : p(o) {}
    ~RamRef() { beNDMWGameRamInfoRam *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};

int Gap__Bec__beNDMWGameRam__vfunc_25(beNDMWGameRam *arg0) {
    beBaseInfoList *infos;
    beBaseInfoRamList *rams;
    int var_v0;
    beNDMWGameRamInfoRam *n;
    infos = (beBaseInfoList *)arg0->_infoList;
    if (infos->_count == 0) {
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = GPR_00554c14 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        InfoRef info(FUN_003ca380(var_v0));
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = GPR_00554c14 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        RamRef ram(FUN_003ca1a0(var_v0));
        igNamedObject_SetName(info.p, &DAT_00518bb8[0]);
        ram.p->_parentInfo = (int)info.p;
        ram.p->_parentManager = (int)arg0;
        n = ram.p;
        n->_st0 = 0;
        n->_st3 = 0;
        n->_st2 = 0;
        n->_st1 = 0;
        ram.p->_ramNo = 0;
        ram.p->_isRun = 1;
        rams = (beBaseInfoRamList *)info.p->_ramList;
        ObjectList_AppendRetained((unsigned)rams, ram.p);
        ObjectList_AppendRetained((unsigned)arg0->_infoList, info.p);
        beMessenger_RegisterReceiverFromInfo(arg0->_messenger, ram.p, &DAT_00518bc0[0]);
    }
    return 0;
}
