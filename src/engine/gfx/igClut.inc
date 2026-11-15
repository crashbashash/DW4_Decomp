igMetaObject *g_igClut_metaObject;
igMetaField *g_igClut_fmtMetaField;
igMetaField *g_igClut_numEntriesMetaField;
igMetaField *g_igClut_strideMetaField;
igMetaField *g_igClut_pDataMetaField;
igMetaField *g_igClut_clutSizeMetaField;
igMetaField *g_igClut_clutDirtyMetaField;
igMetaField *g_igClut_isAlphaScaledMetaField;

int FUN_0014fa50(int arg0) {
    FUN_0014fb70();
    return igMetaObject_CreateInstance(g_igClut_metaObject, arg0);
}

igMetaObject *FUN_0014fa90(void) {
    if (g_igClut_metaObject == 0) {
        g_igClut_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igClut_metaObject;
}

igMetaObject *igClut_GetMetaObject(void)
{
    igMetaObject *g = g_igClut_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014fb70();
    return g_igClut_metaObject;
}

int igClut_GetVTable(void) {
    struct Obj_14fb30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005269f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0014fb70(void)
{
    igMetaObject_RunStaticInit(igClut_Register);
}

void igClut_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igClut_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igClut_GetMetaObject,
        "igClut",
        0x20, /* instance size */
        igClut_GetVTable,
        &igClut_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igClut_GetMetaObject(void) {
    igClut_GetMetaObject();
}

static FieldFactory g_igClut_ctorTable[] = {
    igEnumMetaField_Create,
    igUnsignedIntMetaField_Create,
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igClut_fieldTable[] = {
    "_fmt",
    "_numEntries",
    "_stride",
    "_pData",
    "_clutSize",
    "_clutDirty",
    "_isAlphaScaled",
};
static igMetaField **g_igClut_fieldHandles[] = {
    &g_igClut_fmtMetaField,
    &g_igClut_numEntriesMetaField,
    &g_igClut_strideMetaField,
    &g_igClut_pDataMetaField,
    &g_igClut_clutSizeMetaField,
    &g_igClut_clutDirtyMetaField,
    &g_igClut_isAlphaScaledMetaField,
};
static int g_igClut_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    29,
};

static int g_igClut_fmtDefault = -1;

void igClut_InitFields(void) {
    int fieldStart;
    void *temp_v0_2;
    void *temp_v0;
    void *temp_s1;
    igMetaObject *meta;

    meta = g_igClut_metaObject;
    fieldStart = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igClut_ctorTable, 7);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart));
    igEnumMetaField_SetDefaultValue(temp_v0, &g_igClut_fmtDefault);
    *(int *)((char *)(temp_v0) + 52) = (int)(&igMetaEnum_GetEmpty);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 2), -1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 3));
    *(int *)((char *)(temp_s1) + 60) = igUnsignedCharMetaField_GetDefaultDescriptor();
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, fieldStart + 4), -1);
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(meta, fieldStart + 5));
    igBoolMetaField_SetDefaultValue(temp_v0_2, 1);
    *(char *)((char *)(temp_v0_2) + 38) = 0;
    *(char *)((char *)(igMetaObject_GetFieldAt(meta, fieldStart + 6)) + 38) = 0;
    igMetaObject_NameFields(meta, g_igClut_fieldTable, g_igClut_fieldHandles, g_igClut_fieldOffsets, fieldStart);
    *(int *)((char *)(g_igClut_metaObject) + 60) = (int)(&thunk_igPsx2Clut_GetMetaObject);
}

