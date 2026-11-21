igMetaObject *g_igMultiPassStateAttr_metaObject;
igMetaField *g_igMultiPassStateAttr_numPassesMetaField;

igMultiPassStateAttr *igMultiPassStateAttr_Create(igMemoryPoolView *pool) {
    igMultiPassStateAttr_EnsureRegistered();
    return (igMultiPassStateAttr *)igMetaObject_CreateInstance(g_igMultiPassStateAttr_metaObject, pool);
}

igMetaObject *igMultiPassStateAttr_GetOrCreateMetaObject(void) {
    if (g_igMultiPassStateAttr_metaObject == 0) {
        g_igMultiPassStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMultiPassStateAttr_metaObject;
}

igMetaObject *igMultiPassStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMultiPassStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMultiPassStateAttr_EnsureRegistered();
    return g_igMultiPassStateAttr_metaObject;
}

int igMultiPassStateAttr_GetVTable(void) {
    struct O_135270 o;
    igObject_InitHeader((igObject *)&o.vt);
    o.vt = g_igMultiPassStateAttr_vtable;
    return *(int *)((char *)&o.vt + g_objectSystem->vtableProbeOffset);
}

void igMultiPassStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMultiPassStateAttr_Register);
}

CallbackArray *igMultiPassStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMultiPassStateAttr_metaObject,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        igMultiPassStateAttr_GetMetaObjectFunction,
        "igMultiPassStateAttr",
        0x10, /* instance size */
        igMultiPassStateAttr_GetVTable,
        &igMultiPassStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igMultiPassStateAttr_GetMetaObjectFunction(void) {
    igMultiPassStateAttr_GetMetaObject();
}

static FieldFactory g_igMultiPassStateAttr_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igMultiPassStateAttr_fieldTable[] = {
    "_numPasses",
};
static igMetaField **g_igMultiPassStateAttr_fieldHandles[] = {
    &g_igMultiPassStateAttr_numPassesMetaField,
};
static int g_igMultiPassStateAttr_fieldOffsets[] = {
    12,
};

void igMultiPassStateAttr_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igMultiPassStateAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igMultiPassStateAttr_ctorTable, 1);
    igMetaObject_NameFields(meta, g_igMultiPassStateAttr_fieldTable, g_igMultiPassStateAttr_fieldHandles, g_igMultiPassStateAttr_fieldOffsets, base);
}

