igMetaObject *FUN_0013b070(void) {
    if (g_igAttr_metaObject[0] == 0) {
        g_igAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAttr_metaObject[0];
}

igMetaObject *igAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013b110();
    return g_igAttr_metaObject[0];
}

void FUN_0013b110(void)
{
    igMetaObject_RunStaticInit(igAttr_Register);
}

void igAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAttr_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAttr_GetMetaObject,
        igAttr_className,
        0xC, /* instance size */
        0,
        &igAttr_InitFields,
        FUN_0013b240, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAttr_GetMetaObject(void) {
    igAttr_GetMetaObject();
}

void igAttr_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)g_igAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAttr_ctorTable[0], 2);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    igShortMetaField_SetDefault(temp_v0, -1);
    ((igShortMetaField *)temp_v0)->_persistent = 0;
    igMetaObject_NameFields(temp_s0, &g_igAttr_fieldTable[0], &DAT_00486c60[0], &DAT_00486c68[0], temp_s2);
}

void FUN_0013b240(void) {
    FUN_0013b800();
    igMetaObject_AddRegistrationCallback(&FUN_0013b8a0);
}

