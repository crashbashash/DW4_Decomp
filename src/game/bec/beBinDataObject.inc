igMetaObject *g_beBinDataObject_metaObject;
igMetaField *g_beBinDataObject_dataBufferMetaField;
igMetaField *g_beBinDataObject_dataSizeMetaField;

void *FUN_00343b80(void) {
    igMetaObject *g = g_beBinDataObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00343bd0();
    }
    return g_beBinDataObject_metaObject;
}

void FUN_00343bd0(void)
{
    igMetaObject_RunStaticInit(beBinDataObject_Register);
}

void *beBinDataObject_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beBinDataObject_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beBinDataObject_GetMetaObject,
        "beBinDataObject",
        0x18, /* instance size */
        0,
        beBinDataObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBinDataObject_GetMetaObject(void)
{
    FUN_00343b80();
}

igMetaObject *FUN_00343c80(void) {
    return g_beBaseInfoData_metaObject;
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
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBinDataObject_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beBinDataObject_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(temp_s0, g_beBinDataObject_fieldTable, g_beBinDataObject_fieldHandles, g_beBinDataObject_fieldOffsets, temp_s2);
}

