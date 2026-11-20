igMetaObject *g_igGeometryMaskAttr_metaObject;
igMetaField *g_igGeometryMaskAttr_maskMetaField;

igGeometryMaskAttr *igGeometryMaskAttr_Create(igMemoryPoolView *pool) {
    igGeometryMaskAttr_EnsureRegistered();
    return (igGeometryMaskAttr *)igMetaObject_CreateInstance(g_igGeometryMaskAttr_metaObject, pool);
}

igMetaObject *igGeometryMaskAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryMaskAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGeometryMaskAttr_EnsureRegistered();
    return g_igGeometryMaskAttr_metaObject;
}

int igGeometryMaskAttr_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igGeometryMaskAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igGeometryMaskAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGeometryMaskAttr_Register);
}

CallbackArray *igGeometryMaskAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGeometryMaskAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igGeometryMaskAttr_GetMetaObjectFunction,
        "igGeometryMaskAttr",
        0x10, /* instance size */
        igGeometryMaskAttr_GetVTable,
        &igGeometryMaskAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igGeometryMaskAttr_GetMetaObjectFunction(void) {
    igGeometryMaskAttr_GetMetaObject();
}

static FieldFactory g_igGeometryMaskAttr_ctorTable[] = {
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igGeometryMaskAttr_fieldTable[] = {
    "_mask",
};
static igMetaField **g_igGeometryMaskAttr_fieldHandles[] = {
    &g_igGeometryMaskAttr_maskMetaField,
};
static int g_igGeometryMaskAttr_fieldOffsets[] = {
    12,
};

void igGeometryMaskAttr_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_igGeometryMaskAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igGeometryMaskAttr_ctorTable, 1);
    ((Gap::Core::igUnsignedIntMetaField *)(igMetaObject_GetFieldAt(meta, base)))->setDefault(-1);
    igMetaObject_NameFields(meta, g_igGeometryMaskAttr_fieldTable, g_igGeometryMaskAttr_fieldHandles, g_igGeometryMaskAttr_fieldOffsets, base);
}

