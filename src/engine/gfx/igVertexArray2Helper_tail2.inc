int Gap__Gfx__igVertexArray2Helper__vfunc_22(void) {
    return (int)g_igVertexArray2Helper_metaObject[0];
}

void Gap__Gfx__igVertexArray2Helper__vfunc_55(igVertexArray2Helper *self) {
    igObject *vertexArray;
    vertexArray = (igObject *)(self->_vertexArray);
    if (vertexArray != 0) {
        vertexArray->_refCount = vertexArray->_refCount - 1;
        if (((unsigned long long) ((long long)(int) vertexArray->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(vertexArray);
        }
    }
    self->_vertexArray = 0;
}

