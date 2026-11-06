/* If the transform has an input object (_transformInput, +104), call that object's virtual method
 * at vtable offset 132, then reset the transform's own matrix (_m, +32) to identity with
 * igMatrix44f_SetIdentity. */
#include "dw4/reflected.h"
extern "C" {
int igMatrix44f_SetIdentity(...);  /* Sets a 4x4 float matrix to identity. */
void Gap__Sg__igTransform__vfunc_29(igTransform *self);
}
/* Stand-in class that gives the virtual call its C++ calling sequence
 * (lw t9,0(obj); lw t9,132(t9); jalr t9); vX is the method at offset 132. */
class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(); };
void Gap__Sg__igTransform__vfunc_29(igTransform *self) {
    void **transformInput;

    transformInput = (void **)(self->_transformInput);
    if (transformInput != 0) {
        ((DW4VC_132_0 *)(transformInput))->vX();
        igMatrix44f_SetIdentity(&self->_m[0]);
    }
}
