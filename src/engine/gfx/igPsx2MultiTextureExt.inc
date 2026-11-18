igMetaObject *g_igPsx2MultiTextureExt_metaObject;
igMetaField *g_igPsx2MultiTextureExt_contextMetaField;
igMetaField *g_igPsx2MultiTextureExt_blendFunctionMetaField;
igMetaField *g_igPsx2MultiTextureExt_blendingStateMetaField;
igMetaField *g_igPsx2MultiTextureExt_blendAMetaField;
igMetaField *g_igPsx2MultiTextureExt_blendBMetaField;
igMetaField *g_igPsx2MultiTextureExt_blendCMetaField;
igMetaField *g_igPsx2MultiTextureExt_blendDMetaField;
igMetaField *g_igPsx2MultiTextureExt_blendFIXMetaField;

void FUN_0014d650(void) {
    *(int *)((char *)(g_igMultiTextureExt_metaObject) + 60) = (int)(&igPsx2MultiTextureExt_GetMetaObjectFunction);
}

void igPsx2MultiTextureExt_GetMetaObjectFunction(void) {
    igPsx2MultiTextureExt_GetMetaObject();
}

