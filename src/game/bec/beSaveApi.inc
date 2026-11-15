igMetaObject *g_beSaveApi_metaObject;
igMetaField *g_beSaveApi_orderTypeMetaField;
igMetaField *g_beSaveApi_isConAllChkMetaField;
igMetaField *g_beSaveApi_connectMetaField;
igMetaField *g_beSaveApi_resultMetaField;
igMetaField *g_beSaveApi_isEndMetaField;
igMetaField *g_beSaveApi_dummyCountMetaField;
igMetaField *g_beSaveApi_st0MetaField;
igMetaField *g_beSaveApi_st1MetaField;
igMetaField *g_beSaveApi_st2MetaField;
igMetaField *g_beSaveApi_st3MetaField;
igMetaField *g_beSaveApi_imageWorkMetaField;
igMetaField *g_beSaveApi_mountWorkMetaField;
igMetaField *g_beSaveApi_iconWorkMetaField;

igMetaObject *FUN_0034a000(void) {
    if (g_beSaveApi_metaObject == 0) {
        g_beSaveApi_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSaveApi_metaObject;
}

void *FUN_0034a050(void) {
    unsigned char b;
    if (((void * *)&g_beSaveApi_metaObject)[0] != 0) {
        b = (*(int *)((char *)(((void * *)&g_beSaveApi_metaObject)[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_0034a0a0();
done:
    return ((void * *)&g_beSaveApi_metaObject)[0];
}

void FUN_0034a0a0(void)
{
    igMetaObject_RunStaticInit(beSaveApi_Register);
}

static igMetaObjectCallback g_beSaveApi_callbackList[] = { FUN_0034ad70, 0 };

void *beSaveApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beSaveApi_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveApi_GetMetaObject,
        "beSaveApi",
        0x40, /* instance size */
        0,
        beSaveApi_InitFields,
        0, /* extra callback item */
        g_beSaveApi_callbackList /* callback list */
    );
}

void beSaveApi_GetMetaObject(void)
{
    FUN_0034a050();
}

static FieldFactory g_beSaveApi_ctorTable[] = {
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSaveApi_fieldTable[] = {
    "_orderType",
    "_isConAllChk",
    "_connect",
    "_result",
    "_isEnd",
    "_dummyCount",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
    "_imageWork",
    "_mountWork",
    "_iconWork",
};
static igMetaField **g_beSaveApi_fieldHandles[] = {
    &g_beSaveApi_orderTypeMetaField,
    &g_beSaveApi_isConAllChkMetaField,
    &g_beSaveApi_connectMetaField,
    &g_beSaveApi_resultMetaField,
    &g_beSaveApi_isEndMetaField,
    &g_beSaveApi_dummyCountMetaField,
    &g_beSaveApi_st0MetaField,
    &g_beSaveApi_st1MetaField,
    &g_beSaveApi_st2MetaField,
    &g_beSaveApi_st3MetaField,
    &g_beSaveApi_imageWorkMetaField,
    &g_beSaveApi_mountWorkMetaField,
    &g_beSaveApi_iconWorkMetaField,
};
static int g_beSaveApi_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    8,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
};

void beSaveApi_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSaveApi_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSaveApi_ctorTable, 0xD);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xA));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0034ac90();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_0034ac90();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0034ac90();
    igMetaObject_NameFields(temp_s0, g_beSaveApi_fieldTable, g_beSaveApi_fieldHandles, g_beSaveApi_fieldOffsets, temp_s2);
}

