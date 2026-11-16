igMetaObject *g_beNDMWLoadCtrl2CtrlData_metaObject;
int g_beNDMWLoadCtrl2CtrlData_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadCtrl2CtrlData_isTitleMetaField;
igMetaField *g_beNDMWLoadCtrl2CtrlData_st0MetaField;
igMetaField *g_beNDMWLoadCtrl2CtrlData_st1MetaField;
igMetaField *g_beNDMWLoadCtrl2CtrlData_st2MetaField;
igMetaField *g_beNDMWLoadCtrl2CtrlData_st3MetaField;
igMetaEnum *g_beNDMWLoadCtrl2CtrlData_messageMetaEnum;

void beNDMWLoadCtrl2CtrlData_Create(int arg0) {
    beNDMWLoadCtrl2CtrlData_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadCtrl2CtrlData_metaObject, arg0);
}

void *beNDMWLoadCtrl2CtrlData_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadCtrl2CtrlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLoadCtrl2CtrlData_EnsureRegistered();
    }
    return g_beNDMWLoadCtrl2CtrlData_metaObject;
}

int beNDMWLoadCtrl2CtrlData_GetVTable(void) {
    union U_3c7ad0 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beNDMWLoadCtrl2CtrlData_vtable[0];
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

void beNDMWLoadCtrl2CtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2CtrlData_Register);
}

void *beNDMWLoadCtrl2CtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadCtrl2CtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadCtrl2CtrlData_GetMetaObject,
        "beNDMWLoadCtrl2CtrlData",
        0x24, /* instance size */
        beNDMWLoadCtrl2CtrlData_GetVTable,
        beNDMWLoadCtrl2CtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLoadCtrl2CtrlData_GetMetaObject(void)
{
    beNDMWLoadCtrl2CtrlData_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadCtrl2CtrlData_ctorTable[] = {
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadCtrl2CtrlData_fieldTable[] = {
    "_isTitle",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadCtrl2CtrlData_fieldHandles[] = {
    &g_beNDMWLoadCtrl2CtrlData_isTitleMetaField,
    &g_beNDMWLoadCtrl2CtrlData_st0MetaField,
    &g_beNDMWLoadCtrl2CtrlData_st1MetaField,
    &g_beNDMWLoadCtrl2CtrlData_st2MetaField,
    &g_beNDMWLoadCtrl2CtrlData_st3MetaField,
};
static int g_beNDMWLoadCtrl2CtrlData_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
};

void beNDMWLoadCtrl2CtrlData_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s1;
    void *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)(g_beNDMWLoadCtrl2CtrlData_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWLoadCtrl2CtrlData_ctorTable, 5);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(*(int *)((char *)(temp_s1) + 40), temp_v0);
    temp_v0_2 = (void *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "CTRL");
    *(int *)((char *)(temp_v0_2) + 28) = (int)(&g_beNDMWLoadCtrl2CtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    ((RT *)temp_v0_2)->references = ((RT *)temp_v0_2)->references - 1;
    if (((unsigned long long)(long long)((RT *)temp_v0_2)->references & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    igBoolMetaField_SetDefaultValue(((int)igMetaObject_GetFieldAt(temp_s1, temp_s2)), 1);
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWLoadCtrl2CtrlData_fieldTable, g_beNDMWLoadCtrl2CtrlData_fieldHandles, g_beNDMWLoadCtrl2CtrlData_fieldOffsets, temp_s2);
}

static const char *g_beNDMWLoadCtrl2CtrlData_messageNames[] = {
    "GENERATE",
    "GENERATE_TITLE",
    "CLOSE_WIN",
    "GETCOMMON",
};
static int g_beNDMWLoadCtrl2CtrlData_messageValues[] = {
    0,
    1,
    2,
    3,
};

igMetaEnum *LoadCtrl2Message_GetMetaEnum(void) {
    if (g_beNDMWLoadCtrl2CtrlData_messageMetaEnum == 0) {
        g_beNDMWLoadCtrl2CtrlData_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWLoadCtrl2CtrlData_messageNames, g_beNDMWLoadCtrl2CtrlData_messageValues, 4);
    }
    return g_beNDMWLoadCtrl2CtrlData_messageMetaEnum;
}

