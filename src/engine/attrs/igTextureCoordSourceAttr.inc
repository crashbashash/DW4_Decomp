igMetaObject *g_igTextureCoordSourceAttr_metaObject;
igMetaField *g_igTextureCoordSourceAttr_modeMetaField;
igMetaField *g_igTextureCoordSourceAttr_texCoordIndexMetaField;
igMetaField *g_igTextureCoordSourceAttr_unitIDMetaField;

igTextureCoordSourceAttr *igTextureCoordSourceAttr_Create(igMemoryPoolView *pool) {
    igTextureCoordSourceAttr_EnsureRegistered();
    return (igTextureCoordSourceAttr *)igMetaObject_CreateInstance(g_igTextureCoordSourceAttr_metaObject, pool);
}

igMetaObject *igTextureCoordSourceAttr_GetOrCreateMetaObject(void) {
    if (g_igTextureCoordSourceAttr_metaObject == 0) {
        g_igTextureCoordSourceAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureCoordSourceAttr_metaObject;
}

igMetaObject *igTextureCoordSourceAttr_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igTextureCoordSourceAttr_metaObject != 0) {
        ready = (g_igTextureCoordSourceAttr_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igTextureCoordSourceAttr_EnsureRegistered();
done:
    return g_igTextureCoordSourceAttr_metaObject;
}

int igTextureCoordSourceAttr_GetVTable(void) {
    struct Obj_132680 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTextureCoordSourceAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTextureCoordSourceAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureCoordSourceAttr_Register);
}

CallbackArray *igTextureCoordSourceAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureCoordSourceAttr_metaObject,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        igTextureCoordSourceAttr_GetMetaObjectFunction,
        "igTextureCoordSourceAttr",
        0x18, /* instance size */
        igTextureCoordSourceAttr_GetVTable,
        &igTextureCoordSourceAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igTextureCoordSourceAttr_GetMetaObjectFunction(void) {
    igTextureCoordSourceAttr_GetMetaObject();
}

static FieldFactory g_igTextureCoordSourceAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igTextureCoordSourceAttr_fieldTable[] = {
    "_mode",
    "_texCoordIndex",
    "_unitID",
};
static igMetaField **g_igTextureCoordSourceAttr_fieldHandles[] = {
    &g_igTextureCoordSourceAttr_modeMetaField,
    &g_igTextureCoordSourceAttr_texCoordIndexMetaField,
    &g_igTextureCoordSourceAttr_unitIDMetaField,
};
static int g_igTextureCoordSourceAttr_fieldOffsets[] = {
    12,
    16,
    20,
};

void igTextureCoordSourceAttr_InitFields(void) {
    void *field;
    igMetaObject *meta;
    int base;
    void *field2;

    meta = g_igTextureCoordSourceAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igTextureCoordSourceAttr_ctorTable, 3);
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((Gap::Core::igEnumMetaField *)field2)->setDefault(0);
    ((igEnumMetaField *)field2)->_getMetaEnumFunction = (int)&IG_GFX_TEXTURE_COORD_SOURCE_GetMetaEnum;
    field = igMetaObject_GetFieldAt(meta, base + 2);
    ((igMetaField *)field)->_invarianceFunction = (int)igTextureCoordSourceAttr_SynchronizeCachedUnitID;
    igMetaObject_NameFields(meta, g_igTextureCoordSourceAttr_fieldTable, g_igTextureCoordSourceAttr_fieldHandles, g_igTextureCoordSourceAttr_fieldOffsets, base);
}

