igMetaObject *g_igVertexBlendStateAttr_metaObject;
igMetaField *g_igVertexBlendStateAttr_enabledMetaField;

igMetaObject *igVertexBlendStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVertexBlendStateAttr_EnsureRegistered();
    return g_igVertexBlendStateAttr_metaObject;
}

int igVertexBlendStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVertexBlendStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igVertexBlendStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVertexBlendStateAttr_Register);
}

CallbackArray *igVertexBlendStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexBlendStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igVertexBlendStateAttr_GetMetaObjectFunction,
        "igVertexBlendStateAttr",
        0x10, /* instance size */
        igVertexBlendStateAttr_GetVTable,
        &igVertexBlendStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igVertexBlendStateAttr_GetMetaObjectFunction(void) {
    igVertexBlendStateAttr_GetMetaObject();
}

static FieldFactory g_igVertexBlendStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igVertexBlendStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igVertexBlendStateAttr_fieldHandles[] = {
    &g_igVertexBlendStateAttr_enabledMetaField,
};
static int g_igVertexBlendStateAttr_fieldOffsets[] = {
    12,
};

void igVertexBlendStateAttr_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igVertexBlendStateAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igVertexBlendStateAttr_ctorTable, 1);
    igMetaObject_NameFields(meta, g_igVertexBlendStateAttr_fieldTable, g_igVertexBlendStateAttr_fieldHandles, g_igVertexBlendStateAttr_fieldOffsets, base);
}

