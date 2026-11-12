int FUN_0013aab0(void) {
    if (DAT_0055f448[0] == 0) {
        DAT_0055f448[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f448[0];
}

igMetaObject *igAttrDefaultManager_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrDefaultManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013ab50();
    return g_igAttrDefaultManager_metaObject[0];
}

void FUN_0013ab50(void)
{
    igMetaObject_RunStaticInit(igAttrDefaultManager_Register);
}

void igAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAttrDefaultManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAttrDefaultManager_GetMetaObject,
        igAttrDefaultManager_className,
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

