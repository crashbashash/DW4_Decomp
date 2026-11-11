/* The reference count occupies the low 23 bits of the word at object +4. */


void Gap__Gfx__igVertexStream__vfunc_27(igVertexStream *self) {
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

