igMetaObject *g_igRegistryValue_metaObject;
igMetaField *g_igRegistryValue_sectionMetaField;
igMetaField *g_igRegistryValue_valueMetaField;
igMetaField *g_igRegistryValue_valueNameMetaField;

void * igRegistryValue_Create(int allocator) {
    igRegistryValue_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igRegistryValue_metaObject, (igMemoryPoolView *)allocator));
}

igMetaObject *igRegistryValue_GetMetaObject(void)
{
    igMetaObject *g = g_igRegistryValue_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRegistryValue_EnsureRegistered();
    return g_igRegistryValue_metaObject;
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
    r = *(int *)((char *)&value + g_objectSystem->vtableProbeOffset);
    value._vtable = (int)&g_igRegistryValue_vtable[0];
    ReleaseObjectField(valueName);
    ReleaseObjectField(valueRef);
    return r;
}

void igRegistryValue_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRegistryValue_Register);
}

static igMetaObjectCallback g_igRegistryValue_callbackList[] = { igStringObj_EnsureRegistered, 0 };

CallbackArray *igRegistryValue_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igRegistryValue_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igRegistryValue_GetMetaObjectFunction,
        "igRegistryValue",
        0x14,
        igRegistryValue_GetVTable,
        igRegistryValue_InitFields,
        0,
        g_igRegistryValue_callbackList
    );
}

void igRegistryValue_GetMetaObjectFunction(void) {
    igRegistryValue_GetMetaObject();
}

static FieldFactory g_igRegistryValue_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igRegistryValue_fieldTable[] = {
    "_section",
    "_value",
    "_valueName",
};
static igMetaField **g_igRegistryValue_fieldDescriptors[] = {
    &g_igRegistryValue_sectionMetaField,
    &g_igRegistryValue_valueMetaField,
    &g_igRegistryValue_valueNameMetaField,
};
static int g_igRegistryValue_fieldOffsets[] = {
    8,
    12,
    16,
};

void igRegistryValue_InitFields(void) {
    int base;
    void *valueName;
    void *value;
    void *meta;

    meta = (void *)g_igRegistryValue_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igRegistryValue_ctorTable, 3);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, base), -1);
    value = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)value)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)value)->_construct = 1;
    valueName = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)valueName)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igRefMetaField *)valueName)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igRegistryValue_fieldTable, g_igRegistryValue_fieldDescriptors, g_igRegistryValue_fieldOffsets, base);
}

