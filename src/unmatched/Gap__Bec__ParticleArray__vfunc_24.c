/* The product is computed into a local first and the +36 field is added to it. */
#include "dw4/reflected.h"
int Gap__Bec__ParticleArray__vfunc_24(ParticleArray *arg0, unsigned int arg1) {
    int prod;
    if (arg1 >= (unsigned int) arg0->_arrayIndex) {
        return 0;
    }
    prod = arg1 * arg0->_particleDataSize;
    return arg0->_particleArray + prod;
}
