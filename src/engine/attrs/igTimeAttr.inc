igMetaObject *g_igTimeAttr_metaObject;
igMetaField *g_igTimeAttr_timeMetaField;

igTimeAttr *igTimeAttr_CreateInstance(int allocator) {
    igTimeAttr_EnsureRegistered();
    return (igTimeAttr *)igMetaObject_CreateInstance(g_igTimeAttr_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igTimeAttr_GetOrCreateMetaObject(void) {
    if (g_igTimeAttr_metaObject == 0) {
        g_igTimeAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTimeAttr_metaObject;
}

igMetaObject *igTimeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTimeAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTimeAttr_EnsureRegistered();
    return g_igTimeAttr_metaObject;
}

int igTimeAttr_GetVTable(void) {
    union U_131000 u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igTimeAttr_vtable[0];
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igTimeAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTimeAttr_Register);
}

CallbackArray *igTimeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTimeAttr_metaObject,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        igTimeAttr_GetMetaObjectFunction,
        "igTimeAttr",
        0x18, /* instance size */
        igTimeAttr_GetVTable,
        &igTimeAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igTimeAttr_GetMetaObjectFunction(void) {
    igTimeAttr_GetMetaObject();
}

static FieldFactory g_igTimeAttr_ctorTable[] = {
    (FieldFactory)igLongMetaField_Create,
};
static const char *g_igTimeAttr_fieldTable[] = {
    "_time",
};
static igMetaField **g_igTimeAttr_fieldHandles[] = {
    &g_igTimeAttr_timeMetaField,
};
static int g_igTimeAttr_fieldOffsets[] = {
    16,
};

void igTimeAttr_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igTimeAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTimeAttr_ctorTable, 1);
    ((Gap::Core::igLongMetaField *)(igMetaObject_GetFieldAt(meta, base)))->setDefault(0);
    igMetaObject_NameFields(meta, g_igTimeAttr_fieldTable, g_igTimeAttr_fieldHandles, g_igTimeAttr_fieldOffsets, base);
}

