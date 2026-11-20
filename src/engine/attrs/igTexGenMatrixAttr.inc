igMetaObject *g_igTexGenMatrixAttr_metaObject;
igMetaField *g_igTexGenMatrixAttr_mMetaField;
igMetaField *g_igTexGenMatrixAttr_unitIDMetaField;

igTexGenMatrixAttr *igTexGenMatrixAttr_Create(igMemoryPoolView *pool) {
    igTexGenMatrixAttr_EnsureRegistered();
    return (igTexGenMatrixAttr *)igMetaObject_CreateInstance(g_igTexGenMatrixAttr_metaObject, pool);
}

igMetaObject *igTexGenMatrixAttr_GetOrCreateMetaObject(void) {
    if (g_igTexGenMatrixAttr_metaObject == 0) {
        g_igTexGenMatrixAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTexGenMatrixAttr_metaObject;
}

igMetaObject *igTexGenMatrixAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTexGenMatrixAttr_metaObject != 0) {
        ready = (g_igTexGenMatrixAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igTexGenMatrixAttr_EnsureRegistered();
done:
    return g_igTexGenMatrixAttr_metaObject;
}

int igTexGenMatrixAttr_GetVTable(void) {
    union U_133240 u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igTexGenMatrixAttr_vtable[0];
    igMatrix44f_SetIdentity((float *)&u.b[12]);
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igTexGenMatrixAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTexGenMatrixAttr_Register);
}

CallbackArray *igTexGenMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTexGenMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igTexGenMatrixAttr_GetMetaObjectFunction,
        "igTexGenMatrixAttr",
        0x50, /* instance size */
        igTexGenMatrixAttr_GetVTable,
        &igTexGenMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igTexGenMatrixAttr_GetMetaObjectFunction(void) {
    igTexGenMatrixAttr_GetMetaObject();
}

static FieldFactory g_igTexGenMatrixAttr_ctorTable[] = {
    (FieldFactory)igMatrix44fMetaField_CreateInstance,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igTexGenMatrixAttr_fieldTable[] = {
    "m",
    "_unitID",
};
static igMetaField **g_igTexGenMatrixAttr_fieldHandles[] = {
    &g_igTexGenMatrixAttr_mMetaField,
    &g_igTexGenMatrixAttr_unitIDMetaField,
};
static int g_igTexGenMatrixAttr_fieldOffsets[] = {
    12,
    76,
};

void igTexGenMatrixAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;
    struct Fld *fld;

    meta = g_igTexGenMatrixAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTexGenMatrixAttr_ctorTable, 2);
    field = igMetaObject_GetFieldAt(meta, base);
    FUN_0018c640((igMetaField *)field, igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                   igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)).m);
    fld = (Fld *)igMetaObject_GetFieldAt(meta, base + 1);
    ((igMetaField *)fld)->_invarianceFunction = (int)igTexGenMatrixAttr_SynchronizeCachedUnitID;
    igMetaObject_NameFields(meta, g_igTexGenMatrixAttr_fieldTable, g_igTexGenMatrixAttr_fieldHandles, g_igTexGenMatrixAttr_fieldOffsets, base);
}

