/* 0x003a3bf0 — Gap__Bec__ParticleArray__vfunc_38. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int Gap__Bec__ParticleArray__vfunc_38(ParticleArray *arg0) {
    int var_v0;

    var_v0 = arg0->_hasTextureCoordinates != 0;
    if (var_v0 == 0) {
        var_v0 = arg0->_continuousTime != 0;
    }
    return var_v0 ^ 1;
}
