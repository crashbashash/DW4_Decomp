#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" void igObject_Destroy(void *);
extern "C" int Gap__Bec__beTextureCtrl__vfunc_30(void);
extern "C" int Gap__Bec__beTextureCtrl__vfunc_20(void);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int ObjectList_RemoveFirstRetained(...);
typedef struct { int pad0; int rc; } RefObj;
extern "C" void Gap__Bec__beTextureCtrl__vfunc_32(beTextureCtrl *arg0);
extern "C" int g_beTextureCtrlInfo_metaObject[4];
extern "C" int g_beTextureCtrl_metaObject[4];
struct TextureCtrlWork { char header[8]; int f8; int f12; };
/* The _work object: two list handles at +8 and +12. */
struct TextureCtrlSource { char pad[12]; struct TextureCtrlSource *f12; char pad1[12]; unsigned char f28; char pad2[3]; igObjectList *f32; };
extern "C" struct TextureCtrlWork *FUN_00342630(int);
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" void Gap__Bec__beTextureCtrl__vfunc_29(beTextureCtrl *arg0, struct TextureCtrlSource *arg1);
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class TypeIdVirtual { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v88(); };
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class NewObjectVirtual : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void v132(int); };
struct PropertyRecord { char pad[12]; int f12; };
extern "C" NewObjectVirtual *FUN_00132810(...);
extern "C" PropertyRecord *igProperty_FindByName(...);
extern "C" int emptyString[4];
extern "C" int g_igTextureBindAttr_metaObject[4];
extern "C" int g_propertyNameField[4];
extern "C" void Gap__Bec__beTextureCtrl__vfunc_31(beTextureCtrl *arg0, beBaseInfoRam *arg1);

void Gap__Bec__beTextureCtrl__vfunc_32(beTextureCtrl *arg0) {
    RefObj *temp_a0;

    arg0->_isFirstTime = 1;
    temp_a0 = (RefObj *)arg0->_work;
    if (temp_a0 != 0) {
        temp_a0->rc = (int)((int) (temp_a0->rc - 1));
        if (((unsigned long long) ((long long) temp_a0->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)temp_a0);
            ;
        }
    }
    arg0->_work = 0;
}

int Gap__Bec__beTextureCtrl__vfunc_30(void)
{
    return g_beTextureCtrlInfo_metaObject[0];
}

void Gap__Bec__beTextureCtrl__vfunc_29(beTextureCtrl *arg0, struct TextureCtrlSource *arg1) {
    int temp_s4;
    int var_s3;
    int var_s2;
    int var_v0;
    igObject *old;

    if (arg0->_work == 0) {
        var_v0 = igObject_GetAllocator(arg0);
        if (g_useOwnerAllocator != 0) {
            var_v0 = (int)var_v0;
        } else {
            var_v0 = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
        }
        old = (igObject *)arg0->_work;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)old);
            }
        }
        arg0->_work = (int)FUN_00342630(var_v0);
    }
    arg1 = arg1->f12;
    if (arg1->f28 != 0) {
        temp_s4 = arg1->f32->_count;
        var_s3 = 0;
        if (0 < temp_s4) {
            var_s2 = 0;
            do {
                ObjectList_AppendRetained(((struct TextureCtrlWork *)arg0->_work)->f8, *(int *)((char *)arg1->f32->_data + var_s2));
                var_s3 += 1;
                var_s2 += 4;
            } while (var_s3 < temp_s4);
        }
    } else {
        temp_s4 = arg1->f32->_count;
        var_s3 = 0;
        if (0 < temp_s4) {
            var_s2 = 0;
            do {
                ObjectList_AppendRetained(((struct TextureCtrlWork *)arg0->_work)->f12, *(int *)((char *)arg1->f32->_data + var_s2));
                var_s3 += 1;
                var_s2 += 4;
            } while (var_s3 < temp_s4);
        }
    }
}

/* Owning stack reference to the texture attribute object created per matching property; released
 * on scope exit, after the attribute set has retained it (reference count in the low 23 bits of
 * _refCount). */

void Gap__Bec__beTextureCtrl__vfunc_31(beTextureCtrl *arg0, beBaseInfoRam *arg1) {
    struct { int spA0; int pad[5]; } sa;

    beTextureCtrlAttr *s1;
    int s4;
    int s8;
    int *a2;
    igAttrSet *s3;
    int var_v0;
    beTextureCtrlWork *x;
    PropertyRecord *p;
    TypeIdVirtual *s2;
    int s6;
    int k;
    int s5;
    int s0;
    if (arg0->_isFirstTime != 0) {
        if (((beTextureCtrlInfo *)arg1->_parentInfo)->_isTexture == 0) {
            sa.spA0 = ((igObjectList *)((beTextureCtrlWork *)arg0->_work)->_attributeList)->_count;
            s5 = 0;
            if (0 < sa.spA0) {
                s8 = 0;
                do {
                    x = (beTextureCtrlWork *)arg0->_work;
                    s1 = (beTextureCtrlAttr *)*(int *)(((igObjectList *)x->_attributeList)->_data + s8);
                    a2 = (int *)s1->_name;
                    if (a2 != 0) {
                        a2 = (int *)a2;
                    } else {
                        a2 = &emptyString[0];
                    }
                    p = igProperty_FindByName(x->_textureList, g_propertyNameField[0], a2);
                    if (p != 0) {
                        var_v0 = igObject_GetAllocator(arg0);
                        var_v0 = g_useOwnerAllocator ? var_v0 : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
                        igSmartPointer<NewObjectVirtual> attr(FUN_00132810(var_v0));
                        attr.p->v132(p->f12);
                        s3 = (igAttrSet *)s1->_attrSet;
                        s6 = ((igAttrList *)s3->_attributes)->_count;
                        s4 = 0;
                        if (0 < s6) {
                            s0 = 0;
                            do {
                                k = g_igTextureBindAttr_metaObject[0];
                                s2 = (TypeIdVirtual *)*(int *)(((igAttrList *)s3->_attributes)->_data + s0);
                                if (k == s2->v88()) {
                                    int removed; /* matching construct: the removal out-slot is declared after the holder so it lies below it (+0xb8 under +0xbc) as in retail */
                                    ObjectList_RemoveFirstRetained(&removed, s3->_attributes, s2, 0);
                                    break;
                                }
                                s4++;
                                s0 += 4;
                            } while (s4 < s6);
                        }
                        ObjectList_AppendRetained(s3->_attributes, attr.p);
                    }
                    s5++;
                    s8 += 4;
                } while (s5 < sa.spA0);
            }
        }
        arg0->_isFirstTime = 0;
    }
}

int Gap__Bec__beTextureCtrl__vfunc_20(void)
{
    return g_beTextureCtrl_metaObject[0];
}
