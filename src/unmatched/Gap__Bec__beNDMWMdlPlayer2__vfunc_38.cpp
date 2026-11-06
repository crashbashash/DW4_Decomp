#include "dw4/reflected.h"
extern "C" {
/* reference-counted engine object header: refcount word at +4 */
void igObject_Destroy(igObject *);
igObject *beBaseInfoDataList_Create(int);
int Memory_GetAllocatorBySelector(...);
int igObject_GetAllocator(...);
int bePadManager_GetPadForPlayer(int, int);
int FUN_003a65f0(int, int *, int *);
float FUN_003a68d0();
int beLua__RunNamedChunk(int, int *, int);
/* Player work record: byte at +236, int at +240. */
struct PlayerWorkTail { char p[236]; unsigned char f236; char p2[3]; int f240; };
/* property record: pointer to the work record at +20 */
struct PropertyRecord { char p[16]; int f16; PlayerWorkTail *q; };
PropertyRecord *igProperty_FindByName(...);
extern int DAT_005165c8[4];
extern int DAT_00516608[4];
extern int DAT_00516610[4];
extern int DAT_00516618[4];
extern int DAT_00516620[4];
extern int DAT_00516630[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* matching construct: dummy-virtual class gives arg0 a vtable so v35 dispatches through slot 35 */
class MdlPlayer2VirtualShim { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();  virtual void v35(beBaseInfoRam *, int *); char p[28]; int f32; char p2[8]; int f44; };
extern "C" void Gap__Bec__beNDMWMdlPlayer2__vfunc_38(MdlPlayer2VirtualShim *arg0, beBaseInfoRam *arg1);
void Gap__Bec__beNDMWMdlPlayer2__vfunc_38(MdlPlayer2VirtualShim *arg0, beBaseInfoRam *arg1) {
    PropertyRecord *prop;
    PlayerWorkTail *q;
    float f;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        ObjectRef created(beBaseInfoDataList_Create(a));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        igObject *old = (igObject *)arg1->_dataList;
        if (old != 0) {
            --old->_refCount;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        arg1->_dataList = (int)s0;
    }
    prop = igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], DAT_005165c8);
    q = prop->q;
    if (q->f240 < 10) {
        q->f240 = q->f240 + 1;
    }
    bePadManager_GetPadForPlayer(((beNDMWMdlPlayer2 *)arg0)->_padManager, arg1->_ramNo);
    if (FUN_003a65f0(prop->f16 + 32, DAT_00516608, DAT_00516610) != 0) {
        f = FUN_003a68d0();
        if (q->f236 == 0) {
            if (f < 900.0f) {
                q->f236 = 1;
                arg0->v35(arg1, DAT_00516618);
            }
        } else if (!(f <= 900.0f)) {
            q->f236 = 0;
            arg0->v35(arg1, DAT_00516620);
        }
    } else {
        beLua__RunNamedChunk(((beNDMWMdlPlayer2 *)arg0)->_luaManager, DAT_00516630, 0);
    }
}
