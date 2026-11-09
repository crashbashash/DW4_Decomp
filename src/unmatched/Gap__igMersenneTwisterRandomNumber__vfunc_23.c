#include "dw4/reflected.h"
void Gap__igMersenneTwisterRandomNumber__vfunc_23(igMersenneTwisterRandomNumber *self, unsigned int seed) {
    int i; for (i = 0; i < 624; i++) { self->_mt[i] = seed & 0xFFFF0000; seed = 69069 * seed + 1; self->_mt[i] |= (seed & 0xFFFF0000) >> 16; seed = 69069 * seed + 1; } self->_mti = 624;
}
