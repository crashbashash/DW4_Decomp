igMetaObject *g_beLuaDataObject_metaObject;
igMetaField *g_beLuaDataObject_dataSizeMetaField;
igMetaField *g_beLuaDataObject_dataMetaField;

igMetaObject *FUN_0035b510(void) {
    if (g_beLuaDataObject_metaObject == 0) {
        g_beLuaDataObject_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beLuaDataObject_metaObject;
}

void *FUN_0035b560(void) {
    igMetaObject *g = g_beLuaDataObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035b5f0();
    }
    return g_beLuaDataObject_metaObject;
}

int beLuaDataObject_GetVTable(void) {
    struct Obj_35b5b0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005367c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0035b5f0(void)
{
    igMetaObject_RunStaticInit(beLuaDataObject_Register);
}

void *beLuaDataObject_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLuaDataObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beLuaDataObject_GetMetaObject,
        "beLuaDataObject",
        0x10, /* instance size */
        beLuaDataObject_GetVTable,
        beLuaDataObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLuaDataObject_GetMetaObject(void)
{
    FUN_0035b560();
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
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beLuaDataObject_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beLuaDataObject_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(temp_s0, g_beLuaDataObject_fieldTable, g_beLuaDataObject_fieldHandles, g_beLuaDataObject_fieldOffsets, temp_s2);
}

