igMetaObject *g_igNormalizeNormalsStateAttr_metaObject;
igMetaField *g_igNormalizeNormalsStateAttr_enabledMetaField;

igMetaObject *igNormalizeNormalsStateAttr_GetOrCreateMetaObject(void) {
    if (g_igNormalizeNormalsStateAttr_metaObject == 0) {
        g_igNormalizeNormalsStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNormalizeNormalsStateAttr_metaObject;
}

igMetaObject *igNormalizeNormalsStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igNormalizeNormalsStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNormalizeNormalsStateAttr_EnsureRegistered();
    return g_igNormalizeNormalsStateAttr_metaObject;
}

int igNormalizeNormalsStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igNormalizeNormalsStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igNormalizeNormalsStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNormalizeNormalsStateAttr_Register);
}

CallbackArray *igNormalizeNormalsStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNormalizeNormalsStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igNormalizeNormalsStateAttr_GetMetaObjectFunction,
        "igNormalizeNormalsStateAttr",
        0x10, /* instance size */
        igNormalizeNormalsStateAttr_GetVTable,
        &igNormalizeNormalsStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igNormalizeNormalsStateAttr_GetMetaObjectFunction(void) {
    igNormalizeNormalsStateAttr_GetMetaObject();
}

static FieldFactory g_igNormalizeNormalsStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igNormalizeNormalsStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igNormalizeNormalsStateAttr_fieldHandles[] = {
    &g_igNormalizeNormalsStateAttr_enabledMetaField,
};
static int g_igNormalizeNormalsStateAttr_fieldOffsets[] = {
    12,
};

void igNormalizeNormalsStateAttr_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igNormalizeNormalsStateAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igNormalizeNormalsStateAttr_ctorTable, 1);
    igMetaObject_NameFields(meta, g_igNormalizeNormalsStateAttr_fieldTable, g_igNormalizeNormalsStateAttr_fieldHandles, g_igNormalizeNormalsStateAttr_fieldOffsets, base);
}

