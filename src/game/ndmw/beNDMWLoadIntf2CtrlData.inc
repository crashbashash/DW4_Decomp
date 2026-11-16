igMetaObject *g_beNDMWLoadIntf2CtrlData_metaObject;
int g_beNDMWLoadIntf2CtrlData_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2CtrlData_isRunMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isRdyMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isEntryMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isCanselMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isMesWinMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isSystemMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isNoSelMdlMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_newLoadSelMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isNewMakeMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isRdyCancelMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_oldPadDataMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_st0MetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_st1MetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_st2MetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_st3MetaField;
igMetaEnum *g_beNDMWLoadIntf2CtrlData_messageMetaEnum;

void beNDMWLoadIntf2CtrlData_Create(int arg0) {
    beNDMWLoadIntf2CtrlData_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2CtrlData_metaObject, arg0);
}

void *beNDMWLoadIntf2CtrlData_ResolveMetaObject(void) {
    bool ok;
    if (g_beNDMWLoadIntf2CtrlData_metaObject == 0) goto make;
    ok = !!(g_beNDMWLoadIntf2CtrlData_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWLoadIntf2CtrlData_EnsureRegistered();
done:;
    return g_beNDMWLoadIntf2CtrlData_metaObject;
}

int beNDMWLoadIntf2CtrlData_GetVTable(void) {
    union U_3c4450 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beNDMWLoadIntf2CtrlData_vtable[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return s0;
}

void beNDMWLoadIntf2CtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2CtrlData_Register);
}

void *beNDMWLoadIntf2CtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2CtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2CtrlData_GetMetaObject,
        "beNDMWLoadIntf2CtrlData",
        0x34, /* instance size */
        beNDMWLoadIntf2CtrlData_GetVTable,
        beNDMWLoadIntf2CtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLoadIntf2CtrlData_GetMetaObject(void)
{
    beNDMWLoadIntf2CtrlData_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2CtrlData_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2CtrlData_fieldTable[] = {
    "_isRun",
    "_isRdy",
    "_isEntry",
    "_isCtrl",
    "_isCansel",
    "_isMesWin",
    "_isSystem",
    "_isNoSelMdl",
    "_newLoadSel",
    "_isNewMake",
    "_isRdyCancel",
    "_oldPadData",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2CtrlData_fieldHandles[] = {
    &g_beNDMWLoadIntf2CtrlData_isRunMetaField,
    &g_beNDMWLoadIntf2CtrlData_isRdyMetaField,
    &g_beNDMWLoadIntf2CtrlData_isEntryMetaField,
    &g_beNDMWLoadIntf2CtrlData_isCtrlMetaField,
    &g_beNDMWLoadIntf2CtrlData_isCanselMetaField,
    &g_beNDMWLoadIntf2CtrlData_isMesWinMetaField,
    &g_beNDMWLoadIntf2CtrlData_isSystemMetaField,
    &g_beNDMWLoadIntf2CtrlData_isNoSelMdlMetaField,
    &g_beNDMWLoadIntf2CtrlData_newLoadSelMetaField,
    &g_beNDMWLoadIntf2CtrlData_isNewMakeMetaField,
    &g_beNDMWLoadIntf2CtrlData_isRdyCancelMetaField,
    &g_beNDMWLoadIntf2CtrlData_oldPadDataMetaField,
    &g_beNDMWLoadIntf2CtrlData_st0MetaField,
    &g_beNDMWLoadIntf2CtrlData_st1MetaField,
    &g_beNDMWLoadIntf2CtrlData_st2MetaField,
    &g_beNDMWLoadIntf2CtrlData_st3MetaField,
};
static int g_beNDMWLoadIntf2CtrlData_fieldOffsets[] = {
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    28,
    29,
    32,
    36,
    40,
    44,
    48,
};

void beNDMWLoadIntf2CtrlData_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    void *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)(g_beNDMWLoadIntf2CtrlData_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2CtrlData_ctorTable, 0x10);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "CTRL");
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&g_beNDMWLoadIntf2CtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2CtrlData_fieldTable, g_beNDMWLoadIntf2CtrlData_fieldHandles, g_beNDMWLoadIntf2CtrlData_fieldOffsets, temp_s2);
}

static const char *g_beNDMWLoadIntf2CtrlData_messageNames[] = {
    "GENERATE",
    "LINKCOMMON",
    "ISENTRY",
    "ISRDY",
    "ONCTRL",
    "OFFCTRL",
    "SETSELECT_DATA",
    "SETDIFFICULTMAX",
};
static int g_beNDMWLoadIntf2CtrlData_messageValues[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
};

igMetaEnum *LoadIntf2Message_GetMetaEnum(void) {
    if (g_beNDMWLoadIntf2CtrlData_messageMetaEnum == 0) {
        g_beNDMWLoadIntf2CtrlData_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWLoadIntf2CtrlData_messageNames, g_beNDMWLoadIntf2CtrlData_messageValues, 8);
    }
    return g_beNDMWLoadIntf2CtrlData_messageMetaEnum;
}

