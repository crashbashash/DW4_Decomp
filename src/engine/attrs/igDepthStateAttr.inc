igMetaObject *g_igDepthStateAttr_metaObject;
igMetaField *g_igDepthStateAttr_enabledMetaField;

igDepthStateAttr *igDepthStateAttr_Create(igMemoryPoolView *pool) {
    igDepthStateAttr_EnsureRegistered();
    return (igDepthStateAttr *)igMetaObject_CreateInstance(g_igDepthStateAttr_metaObject, pool);
}

igMetaObject *igDepthStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igDepthStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDepthStateAttr_EnsureRegistered();
    return g_igDepthStateAttr_metaObject;
}

int igDepthStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igDepthStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igDepthStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDepthStateAttr_Register);
}

CallbackArray *igDepthStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igDepthStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igDepthStateAttr_GetMetaObjectFunction,
        "igDepthStateAttr",
        0x10, /* instance size */
        igDepthStateAttr_GetVTable,
        &igDepthStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igDepthStateAttr_GetMetaObjectFunction(void) {
    igDepthStateAttr_GetMetaObject();
}

static FieldFactory g_igDepthStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igDepthStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igDepthStateAttr_fieldHandles[] = {
    &g_igDepthStateAttr_enabledMetaField,
};
static int g_igDepthStateAttr_fieldOffsets[] = {
    12,
};

void igDepthStateAttr_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igDepthStateAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igDepthStateAttr_ctorTable, 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base), 1);
    igMetaObject_NameFields(meta, g_igDepthStateAttr_fieldTable, g_igDepthStateAttr_fieldHandles, g_igDepthStateAttr_fieldOffsets, base);
}

