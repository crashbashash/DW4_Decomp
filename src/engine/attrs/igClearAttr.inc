igMetaObject *g_igClearAttr_metaObject;
igMetaField *g_igClearAttr_clearModeMetaField;
igMetaField *g_igClearAttr_colorMetaField;
igMetaField *g_igClearAttr_accumMetaField;
igMetaField *g_igClearAttr_depthMetaField;
igMetaField *g_igClearAttr_stencilMetaField;
igMetaField *g_igClearAttr_colorPackedMetaField;
igMetaField *g_igClearAttr_depthFMetaField;

igClearAttr *igClearAttr_Create(igMemoryPoolView *pool) {
    igClearAttr_EnsureRegistered();
    return (igClearAttr *)igMetaObject_CreateInstance(g_igClearAttr_metaObject, pool);
}

igMetaObject *igClearAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igClearAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igClearAttr_EnsureRegistered();
    return g_igClearAttr_metaObject;
}

int igClearAttr_GetVTable(void) {
    struct Obj_139400 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igClearAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igClearAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igClearAttr_Register);
}

CallbackArray *igClearAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igClearAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igClearAttr_GetMetaObjectFunction,
        "igClearAttr",
        0x48, /* instance size */
        igClearAttr_GetVTable,
        &igClearAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igClearAttr_GetMetaObjectFunction(void) {
    igClearAttr_GetMetaObject();
}

static FieldFactory g_igClearAttr_ctorTable[] = {
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool,
    (FieldFactory)igDoubleMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
};
static const char *g_igClearAttr_fieldTable[] = {
    "_clearMode",
    "_color",
    "_accum",
    "_depth",
    "_stencil",
    "_colorPacked",
    "_depthF",
};
static igMetaField **g_igClearAttr_fieldHandles[] = {
    &g_igClearAttr_clearModeMetaField,
    &g_igClearAttr_colorMetaField,
    &g_igClearAttr_accumMetaField,
    &g_igClearAttr_depthMetaField,
    &g_igClearAttr_stencilMetaField,
    &g_igClearAttr_colorPackedMetaField,
    &g_igClearAttr_depthFMetaField,
};
static int g_igClearAttr_fieldOffsets[] = {
    12,
    16,
    32,
    48,
    56,
    60,
    64,
};

void igClearAttr_InitFields(void) {
    void *field;
    void *field2;
    void *field3;
    void *field4;
    void *meta;
    int base;

    meta = (void *)g_igClearAttr_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igClearAttr_ctorTable, 7);
    field4 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((Gap::Math::igVec4fMetaField *)field4)->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 1.0f));
    field3 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2));
    ((Gap::Math::igVec4fMetaField *)field3)->setDefault(igVec4f(0.0f, 0.0f, 0.0f, 0.0f));
    ((Gap::Core::igDoubleMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)))->setDefault(1.0);
    field2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    ((Gap::Core::igUnsignedIntMetaField *)field2)->setDefault(-1);
    ((igMetaField *)field2)->_persistent = 0;
    field = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6));
    ((Gap::Core::igFloatMetaField *)field)->setDefault(1.0f);
    ((igMetaField *)field)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igClearAttr_fieldTable, g_igClearAttr_fieldHandles, g_igClearAttr_fieldOffsets, base);
}

