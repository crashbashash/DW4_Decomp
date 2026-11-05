/* 0x00325900
 * Initialise the pool: run the igObject base step (an empty stub, 0x002ff130), take the
 * default `_poolOptionFlags` from the word at 0x004c2608 (6 in the retail
 * image) and clear the 128 bytes that follow the reflected fields (+0x90). */
#include "dw4/reflected.h"
int memset();  /* memset(dst, byte, size); returns dst */
int Gap__Core__igObject__vfunc_11();
extern int g_igPageMemoryPool_defaultPoolOptionFlags_004c2608[4];
void Gap__Core__igPageMemoryPool__vfunc_13(igPageMemoryPool *self) {
    Gap__Core__igObject__vfunc_11();
    self->_poolOptionFlags = g_igPageMemoryPool_defaultPoolOptionFlags_004c2608[0];
    memset((char *)self + 0x90, 0, 0x80);
}
