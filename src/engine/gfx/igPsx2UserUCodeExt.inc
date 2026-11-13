void thunk_igPsx2UserUCodeExt_GetMetaObject(void) {
    igPsx2UserUCodeExt_GetMetaObject();
}

igMetaObject *FUN_0014bc80(void) {
    if (g_igScissorExt_metaObject[0] == 0) {
        g_igScissorExt_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igScissorExt_metaObject[0];
}

