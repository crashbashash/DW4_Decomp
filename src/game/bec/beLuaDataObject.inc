igMetaObject *g_beLuaDataObject_metaObject;
igMetaField *g_beLuaDataObject_dataSizeMetaField;
igMetaField *g_beLuaDataObject_dataMetaField;

igMetaObject *beLuaDataObject_GetOrCreateMetaObject(void) {
    if (g_beLuaDataObject_metaObject == 0) {
        g_beLuaDataObject_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beLuaDataObject_metaObject;
}

void *beLuaDataObject_GetMetaObject(void) {
    igMetaObject *g = g_beLuaDataObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLuaDataObject_EnsureRegistered();
    }
    return g_beLuaDataObject_metaObject;
}

int beLuaDataObject_GetVTable(void) {
    beLuaDataObject obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beLuaDataObject_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beLuaDataObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLuaDataObject_Register);
}

CallbackArray *beLuaDataObject_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLuaDataObject_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beLuaDataObject_GetMetaObjectFunction,
        "beLuaDataObject",
        0x10, /* instance size */
        beLuaDataObject_GetVTable,
        beLuaDataObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLuaDataObject_GetMetaObjectFunction(void)
{
    beLuaDataObject_GetMetaObject();
}

static FieldFactory g_beLuaDataObject_ctorTable[] = {
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
};
static const char *g_beLuaDataObject_fieldTable[] = {
    "_dataSize",
    "_data",
};
static igMetaField **g_beLuaDataObject_fieldHandles[] = {
    &g_beLuaDataObject_dataSizeMetaField,
    &g_beLuaDataObject_dataMetaField,
};
static int g_beLuaDataObject_fieldOffsets[] = {
    8,
    12,
};

void beLuaDataObject_InitFields(void) {
    int base;
    void *data;
    igMetaObject *meta;

    meta = g_beLuaDataObject_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLuaDataObject_ctorTable, 2);
    data = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igMemoryRefMetaField *)data)->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    igMetaObject_NameFields(meta, g_beLuaDataObject_fieldTable, g_beLuaDataObject_fieldHandles, g_beLuaDataObject_fieldOffsets, base);
}

