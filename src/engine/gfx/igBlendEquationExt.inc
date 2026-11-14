igMetaObject *FUN_0014fe60(void) {
    if (g_igBlendEquationExt_metaObject[0] == 0) {
        g_igBlendEquationExt_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igBlendEquationExt_metaObject[0];
}

igMetaObject *igBlendEquationExt_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendEquationExt_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014ff00();
    return g_igBlendEquationExt_metaObject[0];
}

void FUN_0014ff00(void)
{
    igMetaObject_RunStaticInit(igBlendEquationExt_Register);
}

void igBlendEquationExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igBlendEquationExt_metaObject,
        igContextExt_Register,
        igContextExt_GetPublishedMetaObject,
        thunk_igBlendEquationExt_GetMetaObject,
        igBlendEquationExt_className,
        0x18, /* instance size */
        0,
        &igBlendEquationExt_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBlendEquationExt_GetMetaObject(void) {
    igBlendEquationExt_GetMetaObject();
}

void igBlendEquationExt_InitFields(void) {
    int temp_s2;
    void *temp_v0;
    void *temp_s0;

    temp_s0 = (void *)(g_igBlendEquationExt_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igBlendEquationExt_ctorTable[0], 1);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    igEnumMetaField_SetDefaultValue(temp_v0, &DAT_00489138[0]);
    *(int *)((char *)(temp_v0) + 52) = (int)(&igMetaEnum_GetEmpty);
    igMetaObject_NameFields(temp_s0, &g_igBlendEquationExt_fieldTable[0], &DAT_00489128[0], &DAT_00489130[0], temp_s2);
    *(int *)((char *)(g_igBlendEquationExt_metaObject[0]) + 60) = (int)(&thunk_igPsx2BlendEquationExt_GetMetaObject);
}

