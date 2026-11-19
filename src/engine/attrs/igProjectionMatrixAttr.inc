igMetaObject *g_igProjectionMatrixAttr_metaObject;
igMetaField *g_igProjectionMatrixAttr_mMetaField;

igProjectionMatrixAttr *igProjectionMatrixAttr_Create(igMemoryPoolView *pool) {
    igProjectionMatrixAttr_EnsureRegistered();
    return (igProjectionMatrixAttr *)igMetaObject_CreateInstance(g_igProjectionMatrixAttr_metaObject, pool);
}

igMetaObject *igProjectionMatrixAttr_GetOrCreateMetaObject(void) {
    if (g_igProjectionMatrixAttr_metaObject == 0) {
        g_igProjectionMatrixAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igProjectionMatrixAttr_metaObject;
}

igMetaObject *igProjectionMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igProjectionMatrixAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igProjectionMatrixAttr_EnsureRegistered();
    return g_igProjectionMatrixAttr_metaObject;
}

int igProjectionMatrixAttr_GetVTable(void) {
    struct Obj_134770 o;
    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igProjectionMatrixAttr_vtable[0];
    igMatrix44f_SetIdentity((float *)&o.pad[8]);
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igProjectionMatrixAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igProjectionMatrixAttr_Register);
}

CallbackArray *igProjectionMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igProjectionMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igProjectionMatrixAttr_GetMetaObjectFunction,
        "igProjectionMatrixAttr",
        0x4C, /* instance size */
        igProjectionMatrixAttr_GetVTable,
        &igProjectionMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igProjectionMatrixAttr_GetMetaObjectFunction(void) {
    igProjectionMatrixAttr_GetMetaObject();
}

static FieldFactory g_igProjectionMatrixAttr_ctorTable[] = {
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
};
static const char *g_igProjectionMatrixAttr_fieldTable[] = {
    "_m",
};
static igMetaField **g_igProjectionMatrixAttr_fieldHandles[] = {
    &g_igProjectionMatrixAttr_mMetaField,
};
static int g_igProjectionMatrixAttr_fieldOffsets[] = {
    12,
};

void igProjectionMatrixAttr_InitFields(void) {
    int base;
    int field;
    igMetaObject *meta;
    struct M o1;
    struct V o2;
    struct V o3;
    struct V o4;
    struct V o5;

    meta = g_igProjectionMatrixAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igProjectionMatrixAttr_ctorTable, 1);
    field = (int)igMetaObject_GetFieldAt(meta, base);
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    igMatrix44f_FromRows((float *)&o1, (igVec4f *)&o2, (igVec4f *)&o3, (igVec4f *)&o4, (igVec4f *)&o5);
    FUN_0018c640((igMetaField *)field, (const float *)&o1);
    igMetaObject_NameFields(meta, g_igProjectionMatrixAttr_fieldTable, g_igProjectionMatrixAttr_fieldHandles, g_igProjectionMatrixAttr_fieldOffsets, base);
}

