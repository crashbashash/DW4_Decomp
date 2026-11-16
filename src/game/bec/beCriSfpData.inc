igMetaObject *g_beCriSfpData_metaObject;
igMetaField *g_beCriSfpData_portNoMetaField;
igMetaField *g_beCriSfpData_tblSizeMetaField;
igMetaField *g_beCriSfpData_pcmSizeMetaField;
igMetaField *g_beCriSfpData_isTransferMetaField;

igMetaObject *beCriSfpData_GetMetaObject(void) {
    if (g_beCriSfpData_metaObject == 0 || !isValid(g_beCriSfpData_metaObject)) beCriSfpData_EnsureRegistered();
    return g_beCriSfpData_metaObject;
}

int beCriSfpData_GetVTable(void) {
    beCriSfpData obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beCriSfpData_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beCriSfpData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCriSfpData_Register);
}

void *beCriSfpData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCriSfpData_metaObject,
        beBinDataObject_Register,
        beBinDataObject_GetPublishedMetaObject,
        beCriSfpData_GetMetaObjectFunction,
        "beCriSfpData",
        0x28, /* instance size */
        beCriSfpData_GetVTable,
        beCriSfpData_InitFields,
        beCriSfpData_StaticInitCallback, /* extra callback item */
        0 /* callback list */
    );
}

void beCriSfpData_GetMetaObjectFunction(void)
{
    beCriSfpData_GetMetaObject();
}

igMetaObject *beBinDataObject_GetPublishedMetaObject(void) {
    return g_beBinDataObject_metaObject;
}

static FieldFactory g_beCriSfpData_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beCriSfpData_fieldTable[] = {
    "_portNo",
    "_tblSize",
    "_pcmSize",
    "_isTransfer",
};
static igMetaField **g_beCriSfpData_fieldHandles[] = {
    &g_beCriSfpData_portNoMetaField,
    &g_beCriSfpData_tblSizeMetaField,
    &g_beCriSfpData_pcmSizeMetaField,
    &g_beCriSfpData_isTransferMetaField,
};
static int g_beCriSfpData_fieldOffsets[] = {
    24,
    28,
    32,
    36,
};

void beCriSfpData_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beCriSfpData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCriSfpData_ctorTable, 4);
    igMetaObject_NameFields(meta, g_beCriSfpData_fieldTable, g_beCriSfpData_fieldHandles, g_beCriSfpData_fieldOffsets, base);
}

void beCriSfpData_StaticInitCallback(void)
{
    beCriSfpData_SetupBufferAlignment();
}

