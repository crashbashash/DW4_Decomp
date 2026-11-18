igMetaObject *g_igPixelPipelineModeAttr_metaObject;
igMetaField *g_igPixelPipelineModeAttr_pipelineModeMetaField;

igPixelPipelineModeAttr *igPixelPipelineModeAttr_Create(igMemoryPoolView *pool) {
    igPixelPipelineModeAttr_EnsureRegistered();
    return (igPixelPipelineModeAttr *)igMetaObject_CreateInstance(g_igPixelPipelineModeAttr_metaObject, pool);
}

igMetaObject *igPixelPipelineModeAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igPixelPipelineModeAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPixelPipelineModeAttr_EnsureRegistered();
    return g_igPixelPipelineModeAttr_metaObject;
}

int igPixelPipelineModeAttr_GetVTable(void) {
    union U_134bf0 u;

    igObject_InitHeader((igObject *)u.b);
    u.w[0] = (int)(&g_igPixelPipelineModeAttr_vtable[0]);
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igPixelPipelineModeAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPixelPipelineModeAttr_Register);
}

CallbackArray *igPixelPipelineModeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igPixelPipelineModeAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igPixelPipelineModeAttr_GetMetaObjectFunction,
        "igPixelPipelineModeAttr",
        0x10, /* instance size */
        igPixelPipelineModeAttr_GetVTable,
        &igPixelPipelineModeAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igPixelPipelineModeAttr_GetMetaObjectFunction(void) {
    igPixelPipelineModeAttr_GetMetaObject();
}

static FieldFactory g_igPixelPipelineModeAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igPixelPipelineModeAttr_fieldTable[] = {
    "_pipelineMode",
};
static igMetaField **g_igPixelPipelineModeAttr_fieldHandles[] = {
    &g_igPixelPipelineModeAttr_pipelineModeMetaField,
};
static int g_igPixelPipelineModeAttr_fieldOffsets[] = {
    12,
};

void igPixelPipelineModeAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igPixelPipelineModeAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igPixelPipelineModeAttr_ctorTable, 1);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    igEnumMetaField_SetDefaultValue((igMetaField *)field, 0);
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)(&IG_GFX_PIXEL_PIPELINE_MODE_GetMetaEnum);
    igMetaObject_NameFields(meta, g_igPixelPipelineModeAttr_fieldTable, g_igPixelPipelineModeAttr_fieldHandles, g_igPixelPipelineModeAttr_fieldOffsets, base);
}

