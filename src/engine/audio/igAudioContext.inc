void FUN_00142f30(int arg0) {
    FUN_00143010();
    igMetaObject_CreateInstance(*(int *)0x55F540, arg0);
}

igMetaObject *FUN_00142f70(void) {
    if (g_igAudioContext_metaObject[0] == 0) {
        g_igAudioContext_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAudioContext_metaObject[0];
}

igMetaObject *igAudioContext_GetMetaObject(void)
{
    igMetaObject *g = g_igAudioContext_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00143010();
    return g_igAudioContext_metaObject[0];
}

void FUN_00143010(void)
{
    igMetaObject_RunStaticInit(igAudioContext_Register);
}

void igAudioContext_Register(void) {
    AudioLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAudioContext_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAudioContext_GetMetaObject,
        igAudioContext_className,
        0xC, /* instance size */
        0,
        &igAudioContext_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAudioContext_GetMetaObject(void) {
    igAudioContext_GetMetaObject();
}

void igAudioContext_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igAudioContext_metaObject[0]);
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAudioContext_ctorTable[0], 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &g_igAudioContext_fieldTable[0], &DAT_00486ce8[0], &DAT_00486cf0[0], temp_s1);
    *(int *)((char *)(g_igAudioContext_metaObject[0]) + 60) = (int)(thunk_FUN_00143150);
}

void thunk_FUN_00143150(void) {
    FUN_00143150();
}

