igMetaObject *igPsx2VisualContext_GetMeta(void) {
    return g_igPsx2VisualContext_metaObject;
}

void thunk_igObject_InitDefaults(igObject *self) {
    igObject_InitDefaults(self);
}

