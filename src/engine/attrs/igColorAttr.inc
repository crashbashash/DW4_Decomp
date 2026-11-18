igMetaObject *g_igColorAttr_metaObject;
igMetaField *g_igColorAttr_colorMetaField;
igMetaField *g_igColorAttr_colorPackedMetaField;

igColorAttr *igColorAttr_CreateInstance(int allocator) {
    igColorAttr_EnsureRegistered();
    return (igColorAttr *)igMetaObject_CreateInstance(g_igColorAttr_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igColorAttr_GetOrCreateMetaObject(void) {
    if (g_igColorAttr_metaObject == 0) {
        g_igColorAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igColorAttr_metaObject;
}

igMetaObject *igColorAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igColorAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igColorAttr_EnsureRegistered();
    return g_igColorAttr_metaObject;
}

int igColorAttr_GetVTable(void) {
    struct Obj_138fc0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igColorAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igColorAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igColorAttr_Register);
}

CallbackArray *igColorAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igColorAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igColorAttr_GetMetaObjectFunction,
        "igColorAttr",
        0x20, /* instance size */
        igColorAttr_GetVTable,
        &igColorAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igColorAttr_GetMetaObjectFunction(void) {
    igColorAttr_GetMetaObject();
}

static FieldFactory g_igColorAttr_ctorTable[] = {
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igColorAttr_fieldTable[] = {
    "_color",
    "_colorPacked",
};
static igMetaField **g_igColorAttr_fieldHandles[] = {
    &g_igColorAttr_colorMetaField,
    &g_igColorAttr_colorPackedMetaField,
};
static int g_igColorAttr_fieldOffsets[] = {
    12,
    28,
};

void igColorAttr_InitFields(void) {
    void *field;
    void *field2;
    int value[4];
    int base;
    void *field3;
    igMetaObject *meta;

    meta = g_igColorAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igColorAttr_ctorTable, 2);
    field3 = (void *)(igMetaObject_GetFieldAt(meta, base));
    field = (void *)(field3);
    value[0] = 0x3F800000;
    value[1] = 0x3F800000;
    value[2] = 0x3F800000;
    value[3] = 0x3F800000;
    igVec4fMetaField_SetDefault((igMetaField *)field, (const float *)value);
    ((igMetaField *)field3)->_invarianceFunction = (int)&igColorAttr_SynchronizeColorPacked;
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    igUnsignedIntMetaField_SetDefaultValue((igMetaField *)field2, -1);
    ((igMetaField *)field2)->_persistent = 0;
    igMetaObject_NameFields(meta, g_igColorAttr_fieldTable, g_igColorAttr_fieldHandles, g_igColorAttr_fieldOffsets, base);
}

