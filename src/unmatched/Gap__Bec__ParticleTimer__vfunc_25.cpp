#include "dw4/reflected.h"
/* matching construct: dummy-virtual class so ->v100() / ->v132() dispatch through the attribute object's vtable */
class AttributeVtable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int *v100(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void v132(int); };
struct AttributeObjView { int vt; int p4; int p8; AttributeVtable *f12; };
extern "C" {
int igObject_IsKindOf(...);
extern int DAT_0055f170[4];
void Gap__Bec__ParticleTimer__vfunc_25(ParticleTimer *arg0, int arg1);
}
void Gap__Bec__ParticleTimer__vfunc_25(ParticleTimer *arg0, int arg1) {
    igObjectList *temp_s3 = (igObjectList *)arg0->_attributes;
    unsigned int temp_s2 = temp_s3->_count;
    unsigned int var_s1;
    for (var_s1 = 0; var_s1 < temp_s2; var_s1++) {
        AttributeObjView *temp_s0 = (AttributeObjView *)((int *)temp_s3->_data)[var_s1];
        if (temp_s0 != 0 && igObject_IsKindOf(temp_s0, DAT_0055f170[0]) != 0) {
            if (!((((unsigned int)(*temp_s0->f12->v100() & 0xF0)) >> 4) & 0xFF)) {
                ((AttributeVtable *)temp_s0)->v132(arg1);
            }
        }
    }
}
