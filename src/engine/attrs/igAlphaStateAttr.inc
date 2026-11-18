igMetaObject *g_igAlphaStateAttr_metaObject;
igMetaField *g_igAlphaStateAttr_enabledMetaField;

igAlphaStateAttr *igAlphaStateAttr_Create(igMemoryPoolView *pool) {
    igAlphaStateAttr_EnsureRegistered();
    return (igAlphaStateAttr *)igMetaObject_CreateInstance(g_igAlphaStateAttr_metaObject, pool);
}

igMetaObject *igAlphaStateAttr_GetOrCreateMetaObject(void) {
    if (g_igAlphaStateAttr_metaObject == 0) {
        g_igAlphaStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAlphaStateAttr_metaObject;
}

igMetaObject *igAlphaStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAlphaStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAlphaStateAttr_EnsureRegistered();
    return g_igAlphaStateAttr_metaObject;
}

int igAlphaStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAlphaStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAlphaStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAlphaStateAttr_Register);
}

CallbackArray *igAlphaStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAlphaStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igAlphaStateAttr_GetMetaObjectFunction,
        "igAlphaStateAttr",
        0x10, /* instance size */
        igAlphaStateAttr_GetVTable,
        &igAlphaStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igAlphaStateAttr_GetMetaObjectFunction(void) {
    igAlphaStateAttr_GetMetaObject();
}

static FieldFactory g_igAlphaStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igAlphaStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igAlphaStateAttr_fieldHandles[] = {
    &g_igAlphaStateAttr_enabledMetaField,
};
static int g_igAlphaStateAttr_fieldOffsets[] = {
    12,
};

void igAlphaStateAttr_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igAlphaStateAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igAlphaStateAttr_ctorTable, 1);
    igMetaObject_NameFields(meta, g_igAlphaStateAttr_fieldTable, g_igAlphaStateAttr_fieldHandles, g_igAlphaStateAttr_fieldOffsets, base);
}

