/* Getter for the record field at +0x10 of buffer `bufferIndex`. `_pBufList` (+0x364) is an
 * igDataList whose data pointer (+0x10) addresses 0x30-byte VRAM buffer records. */
#include "dw4/reflected.h"
#define BUFFER_RECORD_SIZE 0x30  /* bytes per _pBufList record */
int Gap__Gfx__igPsx2VisualContext__vfunc_55(igPsx2VisualContext *self, int bufferIndex) {
    igDataList *bufList = (igDataList *)self->_pBufList;
    return *(int *)(bufList->_data + bufferIndex * BUFFER_RECORD_SIZE + 16);
}
