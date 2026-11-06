/* Setter for the attribute's particle range. Points the attribute at `particleArray`, a window of
 * `particleNum` particles starting `particleOffset` into it. The array is a reference-counted
 * igObject: the new one is retained and the previous one released, destroyed when its 23-bit count
 * (low bits of the word at +4) reaches zero. */
#include "dw4/reflected.h"
int igObject_Destroy();

void Gap__Attrs__igParticleAttr__vfunc_32(igParticleAttr *self, igObject *particleArray, int particleNum, int particleOffset) {
    igObject *previous;
    if (particleArray != 0) {
        particleArray->_refCount = particleArray->_refCount + 1;
    }
    previous = (igObject *)self->_particleArray;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        /* The shift-and-test spelling of the 23-bit count keeps the dsll32/dsrl32 pair. */
        if (((unsigned long long) ((long long)(int) previous->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(previous);
        }
    }
    self->_particleArray = (int)particleArray;
    self->_particleOffset = particleOffset;
    self->_particleNum = particleNum;
}
