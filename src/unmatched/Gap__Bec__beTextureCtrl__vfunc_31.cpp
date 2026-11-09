#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class TypeIdVirtual { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v88(); };
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class NewObjectVirtual : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void v132(int); };
struct PropertyRecord { char pad[12]; int f12; };
extern "C" {
NewObjectVirtual *FUN_00132810(...);
int Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int ObjectList_RemoveFirstRetained(...);
int igObject_GetAllocator(...);
PropertyRecord *igProperty_FindByName(...);
extern int DAT_004e0858[4];
extern int DAT_0055ed88[4];
extern int DAT_00585be0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beTextureCtrl__vfunc_31(beTextureCtrl *arg0, beBaseInfoRam *arg1);
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
                        a2 = &DAT_004e0858[0];
                    }
                    p = igProperty_FindByName(x->_textureList, DAT_00585be0[0], a2);
                    if (p != 0) {
                        var_v0 = igObject_GetAllocator(arg0);
                        var_v0 = GPR_00554c14 ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                        igSmartPointer<NewObjectVirtual> attr(FUN_00132810(var_v0));
                        attr.p->v132(p->f12);
                        s3 = (igAttrSet *)s1->_attrSet;
                        s6 = ((igAttrList *)s3->_attributes)->_count;
                        s4 = 0;
                        if (0 < s6) {
                            s0 = 0;
                            do {
                                k = DAT_0055ed88[0];
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
