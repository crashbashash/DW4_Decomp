igMetaObject *g_igTextureMatrixStateAttr_metaObject;
igMetaField *g_igTextureMatrixStateAttr_enabledMetaField;
igMetaField *g_igTextureMatrixStateAttr_unitIDMetaField;

igTextureMatrixStateAttr *igTextureMatrixStateAttr_Create(igMemoryPoolView *pool) {
    igTextureMatrixStateAttr_EnsureRegistered();
    return (igTextureMatrixStateAttr *)igMetaObject_CreateInstance(g_igTextureMatrixStateAttr_metaObject, pool);
}

igMetaObject *igTextureMatrixStateAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureMatrixStateAttr_metaObject != 0) {
        ready = (g_igTextureMatrixStateAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igTextureMatrixStateAttr_EnsureRegistered();
done:
    return g_igTextureMatrixStateAttr_metaObject;
}

int igTextureMatrixStateAttr_GetVTable(void) {
    struct Obj_131660 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTextureMatrixStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTextureMatrixStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureMatrixStateAttr_Register);
}

CallbackArray *igTextureMatrixStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureMatrixStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igTextureMatrixStateAttr_GetMetaObjectFunction,
        "igTextureMatrixStateAttr",
        0x14, /* instance size */
        igTextureMatrixStateAttr_GetVTable,
        &igTextureMatrixStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igTextureMatrixStateAttr_GetMetaObjectFunction(void) {
    igTextureMatrixStateAttr_GetMetaObject();
}

static FieldFactory g_igTextureMatrixStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igTextureMatrixStateAttr_fieldTable[] = {
    "_enabled",
    "_unitID",
};
static igMetaField **g_igTextureMatrixStateAttr_fieldHandles[] = {
    &g_igTextureMatrixStateAttr_enabledMetaField,
    &g_igTextureMatrixStateAttr_unitIDMetaField,
};
static int g_igTextureMatrixStateAttr_fieldOffsets[] = {
    12,
    16,
};

void igTextureMatrixStateAttr_InitFields(void) {
    igMetaObject *meta;
    int base;
    struct F *f;

    meta = g_igTextureMatrixStateAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTextureMatrixStateAttr_ctorTable, 2);
    f = (struct F *)igMetaObject_GetFieldAt(meta, base + 1);
    ((igMetaField *)f)->_invarianceFunction = (int)igTextureMatrixStateAttr_SynchronizeCachedUnitID;
    igMetaObject_NameFields(meta, g_igTextureMatrixStateAttr_fieldTable, g_igTextureMatrixStateAttr_fieldHandles, g_igTextureMatrixStateAttr_fieldOffsets, base);
}

