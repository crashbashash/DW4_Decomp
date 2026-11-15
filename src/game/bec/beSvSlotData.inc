igMetaObject *g_beSvSlotData_metaObject;
igMetaField *g_beSvSlotData_isConnectMetaField;
igMetaField *g_beSvSlotData_isFormatMetaField;
igMetaField *g_beSvSlotData_freeSizeMetaField;
igMetaField *g_beSvSlotData_useSizeMetaField;
igMetaField *g_beSvSlotData_totalSizeMetaField;

igMetaObject *FUN_0034aae0(void)
{
    igMetaObject *g = g_beSvSlotData_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0034ab30();
    return g_beSvSlotData_metaObject;
}

void FUN_0034ab30(void)
{
    igMetaObject_RunStaticInit(beSvSlotData_Register);
}

void *beSvSlotData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beSvSlotData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvSlotData_GetMetaObject,
        "beSvSlotData",
        0x18, /* instance size */
        0,
        beSvSlotData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSvSlotData_GetMetaObject(void)
{
    FUN_0034aae0();
}

static FieldFactory g_beSvSlotData_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beSvSlotData_fieldTable[] = {
    "_isConnect",
    "_isFormat",
    "_freeSize",
    "_useSize",
    "_totalSize",
};
static igMetaField **g_beSvSlotData_fieldHandles[] = {
    &g_beSvSlotData_isConnectMetaField,
    &g_beSvSlotData_isFormatMetaField,
    &g_beSvSlotData_freeSizeMetaField,
    &g_beSvSlotData_useSizeMetaField,
    &g_beSvSlotData_totalSizeMetaField,
};
static int g_beSvSlotData_fieldOffsets[] = {
    8,
    9,
    12,
    16,
    20,
};

void beSvSlotData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSvSlotData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSvSlotData_ctorTable, 5);
    igMetaObject_NameFields(temp_s0, g_beSvSlotData_fieldTable, g_beSvSlotData_fieldHandles, g_beSvSlotData_fieldOffsets, temp_s1);
}

