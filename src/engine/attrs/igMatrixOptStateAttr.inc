igMetaObject *g_igMatrixOptStateAttr_metaObject;
igMetaField *g_igMatrixOptStateAttr_enabledMetaField;

igMatrixOptStateAttr *igMatrixOptStateAttr_Create(igMemoryPoolView *pool) {
    igMatrixOptStateAttr_EnsureRegistered();
    return (igMatrixOptStateAttr *)igMetaObject_CreateInstance(g_igMatrixOptStateAttr_metaObject, pool);
}

igMetaObject *igMatrixOptStateAttr_GetOrCreateMetaObject(void) {
    if (g_igMatrixOptStateAttr_metaObject == 0) {
        g_igMatrixOptStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMatrixOptStateAttr_metaObject;
}

igMetaObject *igMatrixOptStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixOptStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMatrixOptStateAttr_EnsureRegistered();
    return g_igMatrixOptStateAttr_metaObject;
}

int igMatrixOptStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMatrixOptStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igMatrixOptStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMatrixOptStateAttr_Register);
}

CallbackArray *igMatrixOptStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMatrixOptStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igMatrixOptStateAttr_GetMetaObjectFunction,
        "igMatrixOptStateAttr",
        0x10, /* instance size */
        igMatrixOptStateAttr_GetVTable,
        &igMatrixOptStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igMatrixOptStateAttr_GetMetaObjectFunction(void) {
    igMatrixOptStateAttr_GetMetaObject();
}

static FieldFactory g_igMatrixOptStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igMatrixOptStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igMatrixOptStateAttr_fieldHandles[] = {
    &g_igMatrixOptStateAttr_enabledMetaField,
};
static int g_igMatrixOptStateAttr_fieldOffsets[] = {
    12,
};

void igMatrixOptStateAttr_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igMatrixOptStateAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igMatrixOptStateAttr_ctorTable, 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base), 1);
    igMetaObject_NameFields(meta, g_igMatrixOptStateAttr_fieldTable, g_igMatrixOptStateAttr_fieldHandles, g_igMatrixOptStateAttr_fieldOffsets, base);
}

