igMetaObject *igTextureUnloadAttr_GetMeta(void) {
    return g_igTextureUnloadAttr_metaObject;
}

/* Setter for the `_texture` field (the texture to unload). */

void igTextureUnloadAttr_SetTexture(igTextureUnloadAttr *self, int texture) {
    self->_texture = texture;
}

