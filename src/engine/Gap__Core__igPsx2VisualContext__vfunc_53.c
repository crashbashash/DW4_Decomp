/* 0x00169b30
 * Read the first two fields of VRAM buffer record `bufferIndex` (0x30-byte
 * records at _pBufList + 0x10, finding #524) into *word0 and *word1;
 * vfunc_52 is the matching setter. */
#include "dw4/reflected.h"
void Gap__Core__igPsx2VisualContext__vfunc_53(igPsx2VisualContext *self, int bufferIndex, int *word0, int *word1) {
    int recordOffset;

    recordOffset = bufferIndex * 0x30;
    *word0 = *(int *)(*(int *)((char *)(self->_pBufList) + 16) + recordOffset);
    *word1 = *(int *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + recordOffset)) + 4);
}
