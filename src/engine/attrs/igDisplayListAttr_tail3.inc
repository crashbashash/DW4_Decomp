igMetaObject *igDisplayListAttr_GetMeta(void) {
    return g_igDisplayListAttr_metaObject;
}

void igDisplayListAttr_Reset(igDisplayListAttr *self) {
    *(int *)((char *)(self->_contents) + 8) = 0;
}

