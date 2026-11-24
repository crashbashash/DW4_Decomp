igMetaObject *g_beBinDataObject_metaObject;
igMetaField *g_beBinDataObject_dataBufferMetaField;
igMetaField *g_beBinDataObject_dataSizeMetaField;

void *beBinDataObject_GetMetaObject(void) {
    igMetaObject *g = g_beBinDataObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beBinDataObject_EnsureRegistered();
    }
    return g_beBinDataObject_metaObject;
}

void beBinDataObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBinDataObject_Register);
}

CallbackArray *beBinDataObject_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beBinDataObject_metaObject,
        Gap::Bec::beBaseInfoData::arkRegisterInternal,
        Gap::Bec::beBaseInfoData::getClassMeta,
        beBinDataObject_GetMetaObjectFunction,
        "beBinDataObject",
        0x18, /* instance size */
        0,
        beBinDataObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBinDataObject_GetMetaObjectFunction(void)
{
    beBinDataObject_GetMetaObject();
}

static FieldFactory g_beBinDataObject_ctorTable[] = {
    igMemoryRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beBinDataObject_fieldTable[] = {
    "_dataBuffer",
    "_dataSize",
};
static igMetaField **g_beBinDataObject_fieldHandles[] = {
    &g_beBinDataObject_dataBufferMetaField,
    &g_beBinDataObject_dataSizeMetaField,
};
static int g_beBinDataObject_fieldOffsets[] = {
    16,
    20,
};

void beBinDataObject_InitFields(void) {
    int base;
    void *dataBuffer;
    igMetaObject *meta;

    meta = g_beBinDataObject_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beBinDataObject_ctorTable, 2);
    dataBuffer = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igMemoryRefMetaField *)dataBuffer)->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    igMetaObject_NameFields(meta, g_beBinDataObject_fieldTable, g_beBinDataObject_fieldHandles, g_beBinDataObject_fieldOffsets, base);
}

