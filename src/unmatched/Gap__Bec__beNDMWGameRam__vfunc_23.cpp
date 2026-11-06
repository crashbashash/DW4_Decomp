/* After the base igObject hook, gives the game ram a fresh common data list and a fresh per-player
 * data-list list, each retained into its field in place of the old one, then initialises the four
 * player slots. */
#include "dw4/reflected.h"
extern "C" {
igObject *FUN_00363e80(int);
igObject *FUN_00364050(int);
int FUN_003f7310(beNDMWGameRam *, int);
int Gap__Core__igObject__vfunc_23(beNDMWGameRam *);
int Memory_GetAllocatorBySelector(int);
void igObject_Destroy(igObject *);
int igObject_GetAllocator(beNDMWGameRam *);
extern int DAT_00587108[4];
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
/* Owning stack reference to the new common data list, released on scope exit (reference count in
 * the low 23 bits of _refCount). */
class CommonDataListRef {
public:
    igObject *p;
    CommonDataListRef(igObject *o) : p(o) {}
    ~CommonDataListRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the new per-player data-list list, released the same way. */
class PlayerDataListListRef {
public:
    igObject *p;
    PlayerDataListListRef(igObject *o) : p(o) {}
    ~PlayerDataListListRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void Gap__Bec__beNDMWGameRam__vfunc_23(beNDMWGameRam *arg0);
void Gap__Bec__beNDMWGameRam__vfunc_23(beNDMWGameRam *arg0) {
    int var_s0;
    int var_v0;
    int var_v0_2;
    igObject *s0;

    Gap__Core__igObject__vfunc_23(arg0);
    var_v0 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0 = (int)var_v0;
    } else {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    {
        /* The new list is owned by the stack reference while it is retained into the field and the old
         * list is released; the reference's own release runs at the block end. */
        CommonDataListRef common(FUN_00364050(var_v0));
        s0 = common.p;
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        ReleaseRef::go((igObject *)arg0->_commonDataList);
        arg0->_commonDataList = (int)s0;
    }
    var_v0_2 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0_2 = (int)var_v0_2;
    } else {
        var_v0_2 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    {
        PlayerDataListListRef players(FUN_00363e80(var_v0_2));
        s0 = players.p;
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        ReleaseRef::go((igObject *)arg0->_playerDataListList);
        arg0->_playerDataListList = (int)s0;
    }
    var_s0 = 0;
    do {
        FUN_003f7310(arg0, var_s0);
        var_s0 += 1;
    } while (var_s0 < 4);
}
