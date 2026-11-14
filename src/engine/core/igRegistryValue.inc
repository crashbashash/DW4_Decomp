void * igRegistryValue_Create(int allocator) {
    igRegistryValue_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585A40), (igMemoryPoolView *)allocator));
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
    value._vtable = (int)&g_igRegistryValue_vtable[0];
    valueRef = &value._value;
    *valueRef = 0;
    valueName = &value._valueName;
    *valueName = 0;
    r = *(int *)((char *)&value + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    value._vtable = (int)&g_igRegistryValue_vtable[0];
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
        0,
        g_igRegistryValue_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igRegistryValue_GetMetaObjectFunction,
        igRegistryValue_className,
        0x14,
        igRegistryValue_GetVTable,
        igRegistryValue_InitFields,
        0,
        (igMetaObjectCallback *)g_igRegistryValue_callbackList
    );
}

void igRegistryValue_GetMetaObjectFunction(void) {
    igRegistryValue_GetMetaObject();
}

void igRegistryValue_InitFields(void) {
    int base;
    void *valueName;
    void *value;
    void *meta;

    meta = (void *)g_igRegistryValue_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igRegistryValue_ctorTable[0], 3);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base))), -1);
    value = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)value)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)value)->_construct = 1;
    valueName = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)valueName)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)valueName)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igRegistryValue_fieldTable[0], (igMetaField ***)&g_igRegistryValue_fieldDescriptors[0], &g_igRegistryValue_fieldOffsets[0], base);
}

