/* 0x0016a4c0
 * Getter for the record field at +0xc of buffer `bufferIndex`: the secondary format (0x20/0x18 in finding #523).
 * `_pBufList` (+0x364) is an igDataList whose data pointer (+0x10) addresses
 * 0x30-byte VRAM buffer records (findings #523/#524). */
#include "dw4/reflected.h"
#define BUFFER_RECORD_SIZE 0x30  /* bytes per _pBufList record (finding #523) */
int Gap__Core__igPsx2VisualContext__vfunc_56(igPsx2VisualContext *self, int bufferIndex) {
    igDataList *bufList = (igDataList *)self->_pBufList;
    return *(int *)(bufList->_data + bufferIndex * BUFFER_RECORD_SIZE + 12);
}
