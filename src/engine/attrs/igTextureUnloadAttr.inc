igMetaObject *g_igTextureUnloadAttr_metaObject;
igMetaField *g_igTextureUnloadAttr_textureMetaField;
igMetaField *g_igTextureUnloadAttr_unitIDMetaField;

igMetaObject *igTextureUnloadAttr_GetOrCreateMetaObject(void) {
    if (g_igTextureUnloadAttr_metaObject == 0) {
        g_igTextureUnloadAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureUnloadAttr_metaObject;
}

igMetaObject *igTextureUnloadAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureUnloadAttr_metaObject != 0) {
        ready = (g_igTextureUnloadAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igTextureUnloadAttr_EnsureRegistered();
done:
    return g_igTextureUnloadAttr_metaObject;
}

int igTextureUnloadAttr_GetVTable(void) {
    struct Obj_131200 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTextureUnloadAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTextureUnloadAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureUnloadAttr_Register);
}

static igMetaObjectCallback g_igTextureUnloadAttr_callbackList[] = { igTextureAttr_EnsureRegistered, 0 };

CallbackArray *igTextureUnloadAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureUnloadAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igTextureUnloadAttr_GetMetaObjectFunction,
        "igTextureUnloadAttr",
        0x14, /* instance size */
        igTextureUnloadAttr_GetVTable,
        &igTextureUnloadAttr_InitFields,
        0, /* extra callback item */
        g_igTextureUnloadAttr_callbackList /* callback list */
    );
}

void igTextureUnloadAttr_GetMetaObjectFunction(void) {
    igTextureUnloadAttr_GetMetaObject();
}

static FieldFactory g_igTextureUnloadAttr_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igTextureUnloadAttr_fieldTable[] = {
    "_texture",
    "_unitID",
};
static igMetaField **g_igTextureUnloadAttr_fieldHandles[] = {
    &g_igTextureUnloadAttr_textureMetaField,
    &g_igTextureUnloadAttr_unitIDMetaField,
};
static int g_igTextureUnloadAttr_fieldOffsets[] = {
    12,
    16,
};

void igTextureUnloadAttr_InitFields(void) {
    int base;
    void *field;
    void *field2;
    igMetaObject *meta;

    meta = g_igTextureUnloadAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTextureUnloadAttr_ctorTable, 2);
    field = igMetaObject_GetFieldAt(meta, base);
    ((igObjectRefMetaField *)field)->_metaObject = (int)igTextureAttr_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field)->_refCounted = 0;
    field2 = igMetaObject_GetFieldAt(meta, base + 1);
    ((igMetaField *)field2)->_invarianceFunction = (int)igTextureUnloadAttr_SynchronizeCachedUnitID;
    igMetaObject_NameFields(meta, g_igTextureUnloadAttr_fieldTable, g_igTextureUnloadAttr_fieldHandles, g_igTextureUnloadAttr_fieldOffsets, base);
}

