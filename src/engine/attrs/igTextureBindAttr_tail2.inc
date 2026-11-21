igMetaObject *igTextureBindAttr_GetMeta(void) {
    return g_igTextureBindAttr_metaObject;
}

/* slot 33 of igTextureBindAttr: set the _texture reference (+12). Reference-counted assignment:
 * retain the new object, release the old one (destroying it when its 23-bit count reaches zero),
 * then store the new one. */
void igTextureBindAttr_SetTexture(igTextureBindAttr *self, igObject *texture) {
    igObject *previousTexture;
    igObject::ref(texture);
    previousTexture = (igObject *)(self->_texture);
    igObject::release(previousTexture);
    self->_texture = (int)texture;
}

