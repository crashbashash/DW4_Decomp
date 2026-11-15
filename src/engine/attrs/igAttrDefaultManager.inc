igMetaObject *g_igAttrDefaultManager_metaObject;

igMetaObject *FUN_0013aab0(void) {
    if (g_igAttrDefaultManager_metaObject == 0) {
        g_igAttrDefaultManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAttrDefaultManager_metaObject;
}

igMetaObject *igAttrDefaultManager_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrDefaultManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013ab50();
    return g_igAttrDefaultManager_metaObject;
}

void FUN_0013ab50(void)
{
    igMetaObject_RunStaticInit(igAttrDefaultManager_Register);
}

void igAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igAttrDefaultManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAttrDefaultManager_GetMetaObject,
        "igAttrDefaultManager",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAttrDefaultManager_GetMetaObject(void) {
    igAttrDefaultManager_GetMetaObject();
}

