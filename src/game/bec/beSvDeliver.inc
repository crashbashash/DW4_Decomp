igMetaObject *g_beSvDeliver_metaObject;
igMetaField *g_beSvDeliver_actConnectMetaField;
igMetaField *g_beSvDeliver_targetConnectMetaField;
igMetaField *g_beSvDeliver_saveVerMetaField;
igMetaField *g_beSvDeliver_resultMetaField;
igMetaField *g_beSvDeliver_operateMetaField;
igMetaField *g_beSvDeliver_memCapaMetaField;
igMetaField *g_beSvDeliver_fileCapaMetaField;
igMetaField *g_beSvDeliver_useMtapMetaField;
igMetaField *g_beSvDeliver_chgUseMtapMetaField;
igMetaField *g_beSvDeliver_isMemCapaOKMetaField;
igMetaField *g_beSvDeliver_isfileCapaOKMetaField;
igMetaField *g_beSvDeliver_isEndOperatMetaField;
igMetaField *g_beSvDeliver_freeSizeListMetaField;
igMetaField *g_beSvDeliver_freeFileListMetaField;
igMetaField *g_beSvDeliver_formatListMetaField;
igMetaField *g_beSvDeliver_totalSizeListMetaField;
igMetaField *g_beSvDeliver_gameDataMetaField;
igMetaField *g_beSvDeliver_platformDataMetaField;

igMetaObject *FUN_0034b0d0(void) {
    if (g_beSvDeliver_metaObject == 0) {
        g_beSvDeliver_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSvDeliver_metaObject;
}

igMetaObject *FUN_0034b120(void) {
    if (g_beSvDeliver_metaObject == 0 || !isValid(g_beSvDeliver_metaObject)) FUN_0034b260();
    return g_beSvDeliver_metaObject;
}

int beSvDeliver_GetVTable(void) {
    union U_34b170 u;
    int temp_s5;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_005388b0[0]);
    u.w[3] = 0;
    u.w[12] = 0;
    u.w[13] = 0;
    u.w[14] = 0;
    u.w[15] = 0;
    u.w[16] = 0;
    temp_s5 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_005388b0[0]);
    FUN_00349080((void **)(&u.w[16]), (long long)(-1));
    igSmartPointer_igIntList_Destruct(&u.w[15], -1);
    igSmartPointer_igIntList_Destruct(&u.w[14], -1);
    igSmartPointer_igIntList_Destruct(&u.w[13], -1);
    igSmartPointer_igIntList_Destruct(&u.w[12], -1);
    igSmartPointer_igIntList_Destruct(&u.w[3], -1);
    return temp_s5;
}

void FUN_0034b260(void)
{
    igMetaObject_RunStaticInit(beSvDeliver_Register);
}

static igMetaObjectCallback g_beSvDeliver_callbackList[] = { igIntList_EnsureRegistered, FUN_0034af90, FUN_0034a340, 0 };

void *beSvDeliver_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvDeliver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSvDeliver_GetMetaObject,
        "beSvDeliver",
        0x44, /* instance size */
        beSvDeliver_GetVTable,
        beSvDeliver_InitFields,
        0, /* extra callback item */
        g_beSvDeliver_callbackList /* callback list */
    );
}

void beSvDeliver_GetMetaObject(void)
{
    FUN_0034b120();
}

static FieldFactory g_beSvDeliver_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igCharMetaField_Create,
    igCharMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSvDeliver_fieldTable[] = {
    "_actConnect",
    "_targetConnect",
    "_saveVer",
    "_result",
    "_operate",
    "_memCapa",
    "_fileCapa",
    "_useMtap",
    "_chgUseMtap",
    "_isMemCapaOK",
    "_isfileCapaOK",
    "_isEndOperat",
    "_freeSizeList",
    "_freeFileList",
    "_formatList",
    "_totalSizeList",
    "_gameData",
    "_platformData",
};
static igMetaField **g_beSvDeliver_fieldHandles[] = {
    &g_beSvDeliver_actConnectMetaField,
    &g_beSvDeliver_targetConnectMetaField,
    &g_beSvDeliver_saveVerMetaField,
    &g_beSvDeliver_resultMetaField,
    &g_beSvDeliver_operateMetaField,
    &g_beSvDeliver_memCapaMetaField,
    &g_beSvDeliver_fileCapaMetaField,
    &g_beSvDeliver_useMtapMetaField,
    &g_beSvDeliver_chgUseMtapMetaField,
    &g_beSvDeliver_isMemCapaOKMetaField,
    &g_beSvDeliver_isfileCapaOKMetaField,
    &g_beSvDeliver_isEndOperatMetaField,
    &g_beSvDeliver_freeSizeListMetaField,
    &g_beSvDeliver_freeFileListMetaField,
    &g_beSvDeliver_formatListMetaField,
    &g_beSvDeliver_totalSizeListMetaField,
    &g_beSvDeliver_gameDataMetaField,
    &g_beSvDeliver_platformDataMetaField,
};
static int g_beSvDeliver_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    41,
    42,
    43,
    44,
    48,
    52,
    56,
    60,
    8,
    64,
};

void beSvDeliver_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;

    temp_s1 = (void *)g_beSvDeliver_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_beSvDeliver_ctorTable, 0x12);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    igCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7), -1);
    igCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8), 0);
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xC));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xD));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xE));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0xF));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x10));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)FUN_0034aeb0();
    ((igObjectRefMetaField *)temp_s2_6)->_refCounted = 0;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 0x11));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)FUN_0034a210();
    igMetaObject_NameFields(temp_s1, g_beSvDeliver_fieldTable, g_beSvDeliver_fieldHandles, g_beSvDeliver_fieldOffsets, temp_s0);
}

