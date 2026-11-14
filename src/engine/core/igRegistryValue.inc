void * igRegistryValue_Create(int arg0) {
    igRegistryValue_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585A40), (igMemoryPoolView *)arg0));
}

igMetaObject *igRegistryValue_GetMetaObject(void)
{
    igMetaObject *g = g_igRegistryValue_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igRegistryValue_EnsureRegistered();
    return g_igRegistryValue_metaObject[0];
}

int igRegistryValue_GetVTable(void) {
    igRegistryValue value;
    int r;
    int *valueRef;
    int *valueName;

    igObject_InitHeader((igObject *)&value);
    value._vtable = (int)&DAT_00532fb0[0];
    valueRef = &value._value;
    *valueRef = 0;
    valueName = &value._valueName;
    *valueName = 0;
    r = *(int *)((char *)&value + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    value._vtable = (int)&DAT_00532fb0[0];
    ReleaseObjectField(valueName);
    ReleaseObjectField(valueRef);
    return r;
}

void igRegistryValue_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igRegistryValue_Register);
}

void igRegistryValue_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igRegistryValue_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igRegistryValue_GetMetaObjectFunction,
        igRegistryValue_className,
        0x14, /* instance size */
        igRegistryValue_GetVTable,
        &igRegistryValue_InitFields,
        0, /* extra callback item */
        g_igRegistryValue_callbackList /* callback list */
    );
}

void igRegistryValue_GetMetaObjectFunction(void) {
    igRegistryValue_GetMetaObject();
}

void igRegistryValue_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igRegistryValue_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igRegistryValue_ctorTable[0], 3);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2))), -1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 2)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igRegistryValue_fieldTable[0], (igMetaField ***)&DAT_004bf938[0], &DAT_004bf948[0], temp_s2);
}

