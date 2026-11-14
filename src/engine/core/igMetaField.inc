igMetaObject *igMetaField_GetOrCreateMetaObject(void) {
    if (g_igMetaField_metaObject[0] == 0) {
        g_igMetaField_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMetaField_metaObject[0];
}

igMetaObject *igMetaField_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaField_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaField_EnsureRegistered();
    return g_igMetaField_metaObject[0];
}

void igMetaField_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaField_Register);
}

void igMetaField_Register(void) {
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igMetaField_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igMetaField_GetMetaObjectFunction,
        igMetaField_className,
        0x34, /* instance size */
        0,
        &igMetaField_InitFields,
        0, /* extra callback item */
        g_igMetaField_callbackList /* callback list */
    );
}

void igMetaField_GetMetaObjectFunction(void) {
    igMetaField_GetMetaObject();
}

void igMetaField_InitFields(void) {
    int temp_s0;
    igObjectRefMetaField *temp_s2;
    igMetaField *temp_v0_3;
    igMemoryRefMetaField *temp_v0_4;
    igMetaField *temp_v0;
    igMetaField *temp_v0_2;
    void *temp_s1;

    temp_s1 = (void *)g_igMetaField_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, (igMetaField * (**)(void *))&g_igMetaField_ctorTable[0], 0x12);
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0))->_persistent = 0;
    temp_v0 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2));
    igShortMetaField_SetDefault((void **)temp_v0, -1);
    temp_v0->_persistent = 0;
    temp_v0_2 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3));
    igShortMetaField_SetDefault((void **)temp_v0_2, -1);
    temp_v0_2->_persistent = 0;
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4))->_persistent = 0;
    temp_s2 = ((igObjectRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5));
    temp_s2->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    temp_s2->_refCounted = 0;
    temp_s2->_persistent = 0;
    temp_s2->_deepCopyMethod = 1;
    temp_s2->_shallowCopyMethod = 1;
    temp_v0_3 = ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6));
    temp_v0_3->_persistent = 0;
    temp_v0_3->_deepCopyMethod = 1;
    temp_v0_4 = ((igMemoryRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7));
    temp_v0_4->_destruct = 1;
    temp_v0_4->_releaseOnCopy = 1;
    temp_v0_4->_releaseOnReset = 1;
    temp_v0_4->_persistent = 0;
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 8), 0);
    igBoolMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xA), 1);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xB), 1);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xC), 0);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xD), 0);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xE), 0);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0xF), 1);
    igCharMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x10), 2);
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 0x11))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, (const char **)&g_igMetaField_fieldTable[0], (igMetaField ***)&DAT_004bfea0[0], &DAT_004bfef0[0], temp_s0);
}

