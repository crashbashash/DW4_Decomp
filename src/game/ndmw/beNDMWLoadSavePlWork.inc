igMetaObject *g_beNDMWLoadSavePlWork_metaObject;
igMetaField *g_beNDMWLoadSavePlWork_isEntryMetaField;
igMetaField *g_beNDMWLoadSavePlWork_isRdyMetaField;
igMetaField *g_beNDMWLoadSavePlWork_isCloseMetaField;
igMetaField *g_beNDMWLoadSavePlWork_isCtrlMetaField;
igMetaField *g_beNDMWLoadSavePlWork_isCutConnectMetaField;
igMetaField *g_beNDMWLoadSavePlWork_utilReturnMetaField;
igMetaField *g_beNDMWLoadSavePlWork_utilNextMetaField;
igMetaField *g_beNDMWLoadSavePlWork_isHaveSaveDataMetaField;
igMetaField *g_beNDMWLoadSavePlWork_haveSaveDataMetaField;
igMetaField *g_beNDMWLoadSavePlWork_sysStat0MetaField;
igMetaField *g_beNDMWLoadSavePlWork_sysStat1MetaField;
igMetaField *g_beNDMWLoadSavePlWork_sysStat2MetaField;
igMetaField *g_beNDMWLoadSavePlWork_sysStat3MetaField;
igMetaField *g_beNDMWLoadSavePlWork_sysCount0MetaField;

void beNDMWLoadSavePlWork_Create(int arg0) {
    FUN_003c5780();
    igMetaObject_CreateInstance(g_beNDMWLoadSavePlWork_metaObject, arg0);
}

void *beNDMWLoadSavePlWork_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadSavePlWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c5780();
    }
    return g_beNDMWLoadSavePlWork_metaObject;
}

int beNDMWLoadSavePlWork_GetVTable(void) {
    struct O_3c5740 o;

    igObject_InitHeader(&o.vt);
    o.vt = DAT_0053ccd0;
    return *(int *)((char *)&o.vt + *(int *)(((char * *)g_objectSystem)[0] + 916));
}

void FUN_003c5780(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSavePlWork_Register);
}

static igMetaObjectCallback g_beNDMWLoadSavePlWork_callbackList[] = { FUN_003c6520, 0 };

void *beNDMWLoadSavePlWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadSavePlWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWLoadSavePlWork_GetMetaObject,
        "beNDMWLoadSavePlWork",
        0x34, /* instance size */
        beNDMWLoadSavePlWork_GetVTable,
        beNDMWLoadSavePlWork_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadSavePlWork_callbackList /* callback list */
    );
}

void beNDMWLoadSavePlWork_GetMetaObject(void)
{
    beNDMWLoadSavePlWork_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadSavePlWork_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadSavePlWork_fieldTable[] = {
    "_isEntry",
    "_isRdy",
    "_isClose",
    "_isCtrl",
    "_isCutConnect",
    "_utilReturn",
    "_utilNext",
    "_isHaveSaveData",
    "_haveSaveData",
    "_sysStat0",
    "_sysStat1",
    "_sysStat2",
    "_sysStat3",
    "_sysCount0",
};
static igMetaField **g_beNDMWLoadSavePlWork_fieldHandles[] = {
    &g_beNDMWLoadSavePlWork_isEntryMetaField,
    &g_beNDMWLoadSavePlWork_isRdyMetaField,
    &g_beNDMWLoadSavePlWork_isCloseMetaField,
    &g_beNDMWLoadSavePlWork_isCtrlMetaField,
    &g_beNDMWLoadSavePlWork_isCutConnectMetaField,
    &g_beNDMWLoadSavePlWork_utilReturnMetaField,
    &g_beNDMWLoadSavePlWork_utilNextMetaField,
    &g_beNDMWLoadSavePlWork_isHaveSaveDataMetaField,
    &g_beNDMWLoadSavePlWork_haveSaveDataMetaField,
    &g_beNDMWLoadSavePlWork_sysStat0MetaField,
    &g_beNDMWLoadSavePlWork_sysStat1MetaField,
    &g_beNDMWLoadSavePlWork_sysStat2MetaField,
    &g_beNDMWLoadSavePlWork_sysStat3MetaField,
    &g_beNDMWLoadSavePlWork_sysCount0MetaField,
};
static int g_beNDMWLoadSavePlWork_fieldOffsets[] = {
    12,
    13,
    14,
    15,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    8,
};

void beNDMWLoadSavePlWork_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWLoadSavePlWork_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWLoadSavePlWork_ctorTable, 0xE);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4), 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 8));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c63a0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, g_beNDMWLoadSavePlWork_fieldTable, g_beNDMWLoadSavePlWork_fieldHandles, g_beNDMWLoadSavePlWork_fieldOffsets, temp_s2);
}

