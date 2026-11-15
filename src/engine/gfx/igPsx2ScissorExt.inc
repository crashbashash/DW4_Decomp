igMetaObject *g_igPsx2ScissorExt_metaObject;
igMetaField *g_igPsx2ScissorExt_contextMetaField;
igMetaField *g_igPsx2ScissorExt_scissorEnableMetaField;
igMetaField *g_igPsx2ScissorExt_scissorOrgXMetaField;
igMetaField *g_igPsx2ScissorExt_scissorOrgYMetaField;
igMetaField *g_igPsx2ScissorExt_scissorWidthMetaField;
igMetaField *g_igPsx2ScissorExt_scissorHeightMetaField;

void FUN_0014bdb0(void) {
    *(int *)((char *)(g_igScissorExt_metaObject) + 60) = (int)(&thunk_igPsx2ScissorExt_GetMetaObject);
}

void thunk_igPsx2ScissorExt_GetMetaObject(void) {
    igPsx2ScissorExt_GetMetaObject();
}

