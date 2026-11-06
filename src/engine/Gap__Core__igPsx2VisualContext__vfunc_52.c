/* Store two words into the first two fields of VRAM buffer record `bufferIndex`. _pBufList
 * (+0x364) holds the 0x30-byte VRAM buffer records at +0x10; vfunc_53 is the matching getter. */
#include "dw4/reflected.h"
int Gap__Core__igPsx2VisualContext__vfunc_52(igPsx2VisualContext *self, int bufferIndex, int word0, int word1) {
    int recordOffset;

    recordOffset = bufferIndex * 0x30;
    *(int *)(*(int *)((char *)(self->_pBufList) + 16) + recordOffset) = word0;
    *(int *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + recordOffset)) + 4) = word1;
    return 1;
}
