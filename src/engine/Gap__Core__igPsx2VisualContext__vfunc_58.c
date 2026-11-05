/* 0x0016a500 igPsx2VisualContext vtable slot 58: reads the float at +24 of one
 * VRAM buffer record (companion of slot 57, which reads the word at +20).
 * _pBufList is the context's table of 0x30-byte buffer records whose element
 * array is at +16 (texture capture, finding #524). */
#include "dw4/reflected.h"
#define VRAM_BUFFER_RECORD_SIZE 0x30
float Gap__Core__igPsx2VisualContext__vfunc_58(igPsx2VisualContext *self, int buffer_index) {
    return *(float *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + (buffer_index * VRAM_BUFFER_RECORD_SIZE))) + 24);
}
