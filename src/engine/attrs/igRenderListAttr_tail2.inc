int Gap__Attrs__igRenderListAttr__vfunc_22(void) {
    return DAT_0055eeb0[0];
}

/* slot 32 of igRenderListAttr: set the _vc reference (+16). Reference-counted assignment: retain
 * the new object, release the old one (destroying it when its 23-bit count reaches zero), then
 * store the new one. */
void Gap__Attrs__igRenderListAttr__vfunc_32(igRenderListAttr *self, igObject *vertexCache) {
    igObject *previousVertexCache;
    if (vertexCache != 0) {
        vertexCache->_refCount = vertexCache->_refCount + 1;
    }
    previousVertexCache = (igObject *)(self->_vc);
    if (previousVertexCache != 0) {
        previousVertexCache->_refCount = previousVertexCache->_refCount - 1;
        if ((previousVertexCache->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(previousVertexCache);
        }
    }
    self->_vc = (int)vertexCache;
}

