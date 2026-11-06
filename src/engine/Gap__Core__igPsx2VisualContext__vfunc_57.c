/* igPsx2VisualContext vtable slot 57: reads the word at +20 of one VRAM buffer record. _pBufList
 * is the context's table of 0x30-byte buffer records whose element array is at +16 (texture
 * capture). */
#include "dw4/reflected.h"
#define VRAM_BUFFER_RECORD_SIZE 0x30
int Gap__Core__igPsx2VisualContext__vfunc_57(igPsx2VisualContext *self, int buffer_index) {
    return *(int *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + (buffer_index * VRAM_BUFFER_RECORD_SIZE))) + 20);
}
