igMetaObject *g_beCriSfpData_metaObject;
igMetaField *g_beCriSfpData_portNoMetaField;
igMetaField *g_beCriSfpData_tblSizeMetaField;
igMetaField *g_beCriSfpData_pcmSizeMetaField;
igMetaField *g_beCriSfpData_isTransferMetaField;

igMetaObject *FUN_00366540(void) {
    if (g_beCriSfpData_metaObject == 0 || !isValid(g_beCriSfpData_metaObject)) FUN_00366620();
    return g_beCriSfpData_metaObject;
}

int beCriSfpData_GetVTable(void) {
    union U u;
    int temp_s0;
    char *q1;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&g_igNamedObject_vtable[0];
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_00535030[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (q1 != 0) {
        temp_v1 = *(int **)q1;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_00366620(void)
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
        beCriSfpData_GetMetaObject,
        "beCriSfpData",
        0x28, /* instance size */
        beCriSfpData_GetVTable,
        beCriSfpData_InitFields,
        FUN_00366760, /* extra callback item */
        0 /* callback list */
    );
}

void beCriSfpData_GetMetaObject(void)
{
    FUN_00366540();
}

igMetaObject *FUN_003666e0(void) {
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
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCriSfpData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beCriSfpData_ctorTable, 4);
    igMetaObject_NameFields(temp_s0, g_beCriSfpData_fieldTable, g_beCriSfpData_fieldHandles, g_beCriSfpData_fieldOffsets, temp_s1);
}

void FUN_00366760(void)
{
    beCriSfpData_SetupBufferAlignment();
}

