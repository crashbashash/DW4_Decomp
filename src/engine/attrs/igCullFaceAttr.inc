igMetaObject *g_igCullFaceAttr_metaObject;
igMetaField *g_igCullFaceAttr_enabledMetaField;
igMetaField *g_igCullFaceAttr_modeMetaField;

igCullFaceAttr *igCullFaceAttr_Create(igMemoryPoolView *pool) {
    igCullFaceAttr_EnsureRegistered();
    return (igCullFaceAttr *)igMetaObject_CreateInstance(g_igCullFaceAttr_metaObject, pool);
}

igMetaObject *igCullFaceAttr_GetOrCreateMetaObject(void) {
    if (g_igCullFaceAttr_metaObject == 0) {
        g_igCullFaceAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCullFaceAttr_metaObject;
}

igMetaObject *igCullFaceAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igCullFaceAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCullFaceAttr_EnsureRegistered();
    return g_igCullFaceAttr_metaObject;
}

int igCullFaceAttr_GetVTable(void) {
    struct Obj_138770 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCullFaceAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igCullFaceAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCullFaceAttr_Register);
}

CallbackArray *igCullFaceAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCullFaceAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igCullFaceAttr_GetMetaObjectFunction,
        "igCullFaceAttr",
        0x14, /* instance size */
        igCullFaceAttr_GetVTable,
        &igCullFaceAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igCullFaceAttr_GetMetaObjectFunction(void) {
    igCullFaceAttr_GetMetaObject();
}

static FieldFactory g_igCullFaceAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
};
static const char *g_igCullFaceAttr_fieldTable[] = {
    "_enabled",
    "_mode",
};
static igMetaField **g_igCullFaceAttr_fieldHandles[] = {
    &g_igCullFaceAttr_enabledMetaField,
    &g_igCullFaceAttr_modeMetaField,
};
static int g_igCullFaceAttr_fieldOffsets[] = {
    12,
    16,
};

void igCullFaceAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;

    meta = g_igCullFaceAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igCullFaceAttr_ctorTable, 2);
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    igEnumMetaField_SetDefaultValue((igMetaField *)field, 0);
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)(&IG_GFX_CULL_FACE_MODE_GetMetaEnum);
    igMetaObject_NameFields(meta, g_igCullFaceAttr_fieldTable, g_igCullFaceAttr_fieldHandles, g_igCullFaceAttr_fieldOffsets, base);
}

