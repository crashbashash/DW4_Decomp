igMetaObject *g_igPsx2UserUCodeExt_metaObject;
igMetaField *g_igPsx2UserUCodeExt_contextMetaField;
igMetaField *g_igPsx2UserUCodeExt_currentDListHandleMetaField;
igMetaField *g_igPsx2UserUCodeExt_pDListsMetaField;
igMetaField *g_igPsx2UserUCodeExt_bCompilingMetaField;

void thunk_igPsx2UserUCodeExt_GetMetaObject(void) {
    igPsx2UserUCodeExt_GetMetaObject();
}

igMetaObject *FUN_0014bc80(void) {
    if (g_igScissorExt_metaObject == 0) {
        g_igScissorExt_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igScissorExt_metaObject;
}

