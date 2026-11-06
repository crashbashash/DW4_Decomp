#include "dw4/reflected.h"
int Gap__Bec__ParticleArray__vfunc_38(ParticleArray *arg0) {
    int var_v0;

    var_v0 = arg0->_hasTextureCoordinates != 0;
    if (var_v0 == 0) {
        var_v0 = arg0->_continuousTime != 0;
    }
    return var_v0 ^ 1;
}
