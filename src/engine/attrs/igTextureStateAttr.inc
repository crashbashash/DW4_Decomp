igMetaObject *g_igTextureStateAttr_metaObject;
igMetaField *g_igTextureStateAttr_enabledMetaField;
igMetaField *g_igTextureStateAttr_unitIDMetaField;

igTextureStateAttr *igTextureStateAttr_CreateInstance(int allocator) {
    igTextureStateAttr_EnsureRegistered();
    return (igTextureStateAttr *)igMetaObject_CreateInstance(g_igTextureStateAttr_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igTextureStateAttr_GetOrCreateMetaObject(void) {
    if (g_igTextureStateAttr_metaObject == 0) {
        g_igTextureStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureStateAttr_metaObject;
}

igMetaObject *igTextureStateAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureStateAttr_metaObject != 0) {
        ready = (g_igTextureStateAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igTextureStateAttr_EnsureRegistered();
done:
    return g_igTextureStateAttr_metaObject;
}

int igTextureStateAttr_GetVTable(void) {
    struct Obj_131470 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTextureStateAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTextureStateAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureStateAttr_Register);
}

CallbackArray *igTextureStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igTextureStateAttr_GetMetaObjectFunction,
        "igTextureStateAttr",
        0x14, /* instance size */
        igTextureStateAttr_GetVTable,
        &igTextureStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igTextureStateAttr_GetMetaObjectFunction(void) {
    igTextureStateAttr_GetMetaObject();
}

static FieldFactory g_igTextureStateAttr_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igTextureStateAttr_fieldTable[] = {
    "_enabled",
    "_unitID",
};
static igMetaField **g_igTextureStateAttr_fieldHandles[] = {
    &g_igTextureStateAttr_enabledMetaField,
    &g_igTextureStateAttr_unitIDMetaField,
};
static int g_igTextureStateAttr_fieldOffsets[] = {
    12,
    16,
};

void igTextureStateAttr_InitFields(void) {
    int base;
    void *field;
    igMetaObject *meta;
    meta = g_igTextureStateAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTextureStateAttr_ctorTable, 2);
    field = igMetaObject_GetFieldAt(meta, base + 1);
    ((igMetaField *)field)->_invarianceFunction = (int)igTextureStateAttr_SynchronizeCachedUnitID;
    igMetaObject_NameFields(meta, g_igTextureStateAttr_fieldTable, g_igTextureStateAttr_fieldHandles, g_igTextureStateAttr_fieldOffsets, base);
}

