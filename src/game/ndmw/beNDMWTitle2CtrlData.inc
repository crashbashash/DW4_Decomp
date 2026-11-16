igMetaObject *g_beNDMWTitle2CtrlData_metaObject;
int g_beNDMWTitle2CtrlData_nameExternalEnumStorage;
igMetaField *g_beNDMWTitle2CtrlData_isRunMetaField;
igMetaField *g_beNDMWTitle2CtrlData_logoCountMetaField;
igMetaField *g_beNDMWTitle2CtrlData_gameMenuCntMetaField;
igMetaField *g_beNDMWTitle2CtrlData_gameMenuNextMetaField;
igMetaField *g_beNDMWTitle2CtrlData_st0MetaField;
igMetaField *g_beNDMWTitle2CtrlData_st1MetaField;
igMetaField *g_beNDMWTitle2CtrlData_st2MetaField;
igMetaField *g_beNDMWTitle2CtrlData_st3MetaField;
igMetaEnum *g_beNDMWTitle2CtrlData_messageMetaEnum;

void beNDMWTitle2CtrlData_Create(int arg0) {
    beNDMWTitle2CtrlData_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWTitle2CtrlData_metaObject, arg0);
}

void *beNDMWTitle2CtrlData_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWTitle2CtrlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWTitle2CtrlData_EnsureRegistered();
    }
    return g_beNDMWTitle2CtrlData_metaObject;
}

int beNDMWTitle2CtrlData_GetVTable(void) {
    union U_3b25f0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beNDMWTitle2CtrlData_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
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

void beNDMWTitle2CtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2CtrlData_Register);
}

void *beNDMWTitle2CtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWTitle2CtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWTitle2CtrlData_GetMetaObjectFunction,
        "beNDMWTitle2CtrlData",
        0x30, /* instance size */
        beNDMWTitle2CtrlData_GetVTable,
        beNDMWTitle2CtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWTitle2CtrlData_GetMetaObjectFunction(void)
{
    beNDMWTitle2CtrlData_GetMetaObject();
}

static FieldFactory g_beNDMWTitle2CtrlData_ctorTable[] = {
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWTitle2CtrlData_fieldTable[] = {
    "_isRun",
    "_logoCount",
    "_gameMenuCnt",
    "_gameMenuNext",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWTitle2CtrlData_fieldHandles[] = {
    &g_beNDMWTitle2CtrlData_isRunMetaField,
    &g_beNDMWTitle2CtrlData_logoCountMetaField,
    &g_beNDMWTitle2CtrlData_gameMenuCntMetaField,
    &g_beNDMWTitle2CtrlData_gameMenuNextMetaField,
    &g_beNDMWTitle2CtrlData_st0MetaField,
    &g_beNDMWTitle2CtrlData_st1MetaField,
    &g_beNDMWTitle2CtrlData_st2MetaField,
    &g_beNDMWTitle2CtrlData_st3MetaField,
};
static int g_beNDMWTitle2CtrlData_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
};

void beNDMWTitle2CtrlData_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    void *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)(g_beNDMWTitle2CtrlData_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWTitle2CtrlData_ctorTable, 8);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "CTRL");
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&g_beNDMWTitle2CtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    *(int *)((char *)(temp_v0_2) + 4) = (int)((int) (*(int *)((char *)(temp_v0_2) + 4) - 1));
    if (((unsigned long long) ((long long) *(int *)((char *)(temp_v0_2) + 4) << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWTitle2CtrlData_fieldTable, g_beNDMWTitle2CtrlData_fieldHandles, g_beNDMWTitle2CtrlData_fieldOffsets, temp_s2);
}

static const char *g_beNDMWTitle2CtrlData_messageNames[] = {
    "RUN",
    "GAMESTART",
};
static int g_beNDMWTitle2CtrlData_messageValues[] = {
    0,
    1,
};

igMetaEnum *FUN_003b2840(void) {
    if (g_beNDMWTitle2CtrlData_messageMetaEnum == 0) {
        g_beNDMWTitle2CtrlData_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWTitle2CtrlData_messageNames, g_beNDMWTitle2CtrlData_messageValues, 2);
    }
    return g_beNDMWTitle2CtrlData_messageMetaEnum;
}

