int igTextureCoordSourceAttr_GetMeta(void) {
    return (int)g_igTextureCoordSourceAttr_metaObject;
}

/* Setter for the `_mode` enum field. Companion of vfunc_33, which sets `_texCoordIndex`. */

void igTextureCoordSourceAttr_SetMode(igTextureCoordSourceAttr *self, int mode) {
    self->_mode = mode;
}

/* Setter for the `_texCoordIndex` field. Companion of vfunc_32, which sets `_mode`. */

void igTextureCoordSourceAttr_SetTexCoordIndex(igTextureCoordSourceAttr *self, int texCoordIndex) {
    self->_texCoordIndex = texCoordIndex;
}

