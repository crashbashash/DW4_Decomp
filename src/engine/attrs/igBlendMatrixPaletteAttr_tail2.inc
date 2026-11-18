igMetaObject *igBlendMatrixPaletteAttr_GetMeta(void) {
    return g_igBlendMatrixPaletteAttr_metaObject;
}

void igBlendMatrixPaletteAttr_UserPostLoad(Obj_1429d0 *arg0) {
    if (arg0->f24 == 0) {
        arg0->f24 = arg0->f20;
    }
}

