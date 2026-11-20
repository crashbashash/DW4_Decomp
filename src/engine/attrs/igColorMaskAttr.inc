igMetaObject *g_igColorMaskAttr_metaObject;
igMetaField *g_igColorMaskAttr_redMetaField;
igMetaField *g_igColorMaskAttr_greenMetaField;
igMetaField *g_igColorMaskAttr_blueMetaField;
igMetaField *g_igColorMaskAttr_alphaMetaField;
igMetaField *g_igColorMaskAttr_unusedMetaField;

igColorMaskAttr *igColorMaskAttr_Create(igMemoryPoolView *pool) {
    igColorMaskAttr_EnsureRegistered();
    return (igColorMaskAttr *)igMetaObject_CreateInstance(g_igColorMaskAttr_metaObject, pool);
}

igMetaObject *igColorMaskAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igColorMaskAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igColorMaskAttr_EnsureRegistered();
    return g_igColorMaskAttr_metaObject;
}

int igColorMaskAttr_GetVTable(void) {
    struct Obj_138d40 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igColorMaskAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igColorMaskAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igColorMaskAttr_Register);
}

CallbackArray *igColorMaskAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igColorMaskAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igColorMaskAttr_GetMetaObjectFunction,
        "igColorMaskAttr",
        0x14, /* instance size */
        igColorMaskAttr_GetVTable,
        &igColorMaskAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igColorMaskAttr_GetMetaObjectFunction(void) {
    igColorMaskAttr_GetMetaObject();
}

static FieldFactory g_igColorMaskAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igColorMaskAttr_fieldTable[] = {
    "_red",
    "_green",
    "_blue",
    "_alpha",
    "_unused",
};
static igMetaField **g_igColorMaskAttr_fieldHandles[] = {
    &g_igColorMaskAttr_redMetaField,
    &g_igColorMaskAttr_greenMetaField,
    &g_igColorMaskAttr_blueMetaField,
    &g_igColorMaskAttr_alphaMetaField,
    &g_igColorMaskAttr_unusedMetaField,
};
static int g_igColorMaskAttr_fieldOffsets[] = {
    12,
    13,
    14,
    15,
    16,
};

void igColorMaskAttr_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igColorMaskAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igColorMaskAttr_ctorTable, 5);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 1)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 2)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 3)))->setDefault(1);
    igMetaObject_NameFields(meta, g_igColorMaskAttr_fieldTable, g_igColorMaskAttr_fieldHandles, g_igColorMaskAttr_fieldOffsets, base);
}

