#include "dw4/reflected.h"
/* matching construct: PropV carries 35 dummy virtuals so vX() dispatches through vtable offset 148 (lw t9,0(a0); lw t9,148(t9); jalr t9) */
struct PropV { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void vX(void *); };
struct Prop { char pad[16]; PropV *f16; };
extern "C" {
igObject *beBaseInfoDataList_Create(...);
int FUN_001910c0(void *, float, float, float);
int Matrix44_Copy(...);
int Matrix44_SetTranslation(...);
int Memory_GetAllocatorBySelector(...);
int beMessenger_GetMatrix(...);
int beMessenger_GetMatrixCount(...);
int beMessenger_GetVec3(...);
int beMessenger_GetVec3Count(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
struct Prop *igProperty_FindByName(...);
extern int DAT_0050ef60[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" void FUN_00396740(beModelCtrl *arg0, beBaseInfoRam *arg1);
void FUN_00396740(beModelCtrl *arg0, beBaseInfoRam *arg1) {
    volatile float spD0[3];
    float spC0[4];
    float sp80[16];
    float sp40[16];
    int var_v0;
    igObject *s1;
    igObject *t;
    struct Prop *prop;
    if (arg1->_dataList == 0) {
        var_v0 = igObject_GetAllocator(arg1);
        if (GPR_00554c14 != 0) {
            var_v0 = (int)var_v0;
        } else {
            var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        {
            ObjectRef r(beBaseInfoDataList_Create(var_v0));
            s1 = r.p;
            if (s1 != 0) {
                s1->_refCount = s1->_refCount + 1;
            }
            t = (igObject *)arg1->_dataList;
            if (t != 0) {
                t->_refCount = t->_refCount - 1;
                if ((t->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(t);
                }
            }
            arg1->_dataList = (int)s1;
        }
    }
    prop = igProperty_FindByName((void *)arg1->_dataList, DAT_00585be0[0], &DAT_0050ef60[0]);
    if (beMessenger_GetVec3Count(arg0->_messenger) != 0) {
        Matrix44_Copy(sp80, (char *)prop->f16 + 0x20);
        beMessenger_GetVec3(spC0, arg0->_messenger, 0);
        Matrix44_SetTranslation(sp80, spC0);
        if (beMessenger_GetVec3Count(arg0->_messenger) == 2) {
            beMessenger_GetVec3(spD0, arg0->_messenger, 1);
            float x = spD0[0];
            FUN_001910c0(sp80, 0.017453292f * x, 0.017453292f * spD0[1], 0.017453292f * spD0[2]);
        }
        prop->f16->vX(sp80);
        return;
    }
    if (beMessenger_GetMatrixCount(arg0->_messenger) != 0) {
        beMessenger_GetMatrix(sp40, arg0->_messenger, 0);
        prop->f16->vX(sp40);
    }
}
