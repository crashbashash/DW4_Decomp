int igVertexArray2Helper_GetMeta(void) {
    return (int)g_igVertexArray2Helper_metaObject;
}

void Gap__Gfx__igVertexArray2Helper__vfunc_55(igVertexArray2Helper *self) {
    igObject *vertexArray;
    vertexArray = (igObject *)(self->_vertexArray);
    igObject::release(vertexArray);
    self->_vertexArray = 0;
}

