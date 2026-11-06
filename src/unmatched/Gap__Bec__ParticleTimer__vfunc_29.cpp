#include "dw4/reflected.h"
extern "C" {
class ParticleAttributeObj;
struct FieldOffsetHolder { char pad[8]; int f8; };
extern FieldOffsetHolder *DAT_00562768[4];
/* matching construct: dummy-virtual class so ->vX() dispatches through the attribute object's vtable */
class ParticleAttributeObj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(); };
void Gap__Bec__ParticleTimer__vfunc_29(ParticleAttributeObj *arg0);
void Gap__Bec__ParticleTimer__vfunc_29(ParticleAttributeObj *arg0) {
    /* matching construct: a typed view of the receiver declared first; a cast at each use changes how the compiler hoists the field address */
    ParticleTimer *self = (ParticleTimer *)arg0;
    unsigned temp_s1;
    unsigned var_s0;
    ParticleAttributeObj *temp_a0_2;

    temp_s1 = ((igObjectList *)self->_attributes)->_count;
    for (var_s0 = 0; var_s0 < temp_s1; var_s0++) {
        ((ParticleAttributeObj **)((igObjectList *)self->_attributes)->_data)[var_s0]->vX();
    }
    temp_a0_2 = *(ParticleAttributeObj **)((char *)arg0 + DAT_00562768[0]->f8);
    if (temp_a0_2 != 0) {
        temp_a0_2->vX();
    }
}
}
