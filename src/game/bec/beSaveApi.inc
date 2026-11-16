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

igMetaObject *beSaveApi_GetOrCreateMetaObject(void) {
    if (g_beSaveApi_metaObject == 0) {
        g_beSaveApi_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSaveApi_metaObject;
}

void *beSaveApi_GetMetaObject(void) {
    unsigned char b;
    if (g_beSaveApi_metaObject != 0) {
        b = (g_beSaveApi_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beSaveApi_EnsureRegistered();
done:
    return g_beSaveApi_metaObject;
}

void beSaveApi_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSaveApi_Register);
}

static igMetaObjectCallback g_beSaveApi_callbackList[] = { beSaveMemoryObj_EnsureRegistered, 0 };

void *beSaveApi_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beSaveApi_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveApi_GetMetaObjectFunction,
        "beSaveApi",
        0x40, /* instance size */
        0,
        beSaveApi_InitFields,
        0, /* extra callback item */
        g_beSaveApi_callbackList /* callback list */
    );
}

void beSaveApi_GetMetaObjectFunction(void)
{
    beSaveApi_GetMetaObject();
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
    int base;
    void *iconWork;
    void *mountWork;
    void *imageWork;
    void *meta;

    meta = (void *)g_beSaveApi_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSaveApi_ctorTable, 0xD);
    imageWork = (void *)(igMetaObject_GetFieldAt(meta, base + 0xA));
    ((igObjectRefMetaField *)imageWork)->_metaObject = (int)beSaveMemoryObj_GetOrCreateMetaObject();
    mountWork = (void *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    ((igObjectRefMetaField *)mountWork)->_metaObject = (int)beSaveMemoryObj_GetOrCreateMetaObject();
    iconWork = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igObjectRefMetaField *)iconWork)->_metaObject = (int)beSaveMemoryObj_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beSaveApi_fieldTable, g_beSaveApi_fieldHandles, g_beSaveApi_fieldOffsets, base);
}

