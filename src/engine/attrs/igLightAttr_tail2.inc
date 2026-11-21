igMetaObject *igLightAttr_GetMeta(void) {
    return g_igLightAttr_metaObject;
}

/* slot 40 of igLightAttr: set the _vc reference (+140). Reference-counted assignment: retain the
 * new object, release the old one (destroying it when its 23-bit count reaches zero), then store
 * the new one. */
void igLightAttr_SetVisualContext(igLightAttr *self, igObject *vertexCache) {
    igObject *previousVertexCache;
    igObject::ref(vertexCache);
    previousVertexCache = (igObject *)(self->_vc);
    igObject::release(previousVertexCache);
    self->_vc = (int)vertexCache;
}

