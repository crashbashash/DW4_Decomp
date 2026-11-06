/* Reset step of an igVertexStream: clears the configured flag and releases the vertex data list
 * (_vertexDataList, an igObjectRefMetaField). The release is the engine's usual reference drop:
 * decrement the count at object +4 and destroy the object when its low 23 bits reach zero. */
#include "dw4/reflected.h"
int igObject_Destroy();

/* The reference count occupies the low 23 bits of the word at object +4. */
#define REF_COUNT_MASK 0x7FFFFF

void Gap__Core__igVertexStream__vfunc_27(igVertexStream *self) {
    igObject *vertexDataList;

    self->_isConfigured = 0;
    vertexDataList = (igObject *)(self->_vertexDataList);
    if (vertexDataList != 0) {
        vertexDataList->_refCount -= 1;
        if ((vertexDataList->_refCount & REF_COUNT_MASK) == 0) {
            igObject_Destroy(vertexDataList);
        }
    }
    self->_vertexDataList = 0;
}
