igMetaObject *g_beNDMWLoadIntf2DataSelIntf_metaObject;
int g_beNDMWLoadIntf2DataSelIntf_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_mcSelPointMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_svDataSelPointMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_comMdlCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_textOrderMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_commonIntfMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_mesWinMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_statDispMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isSaveAreaMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isUpStatWinMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isDownStatWinMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isSlotWinMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isSelCurMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_kindMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_plNoMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_mesKindMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_resultMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isEndMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isCancelMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_st0MetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_st1MetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_st2MetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_st3MetaField;

void beNDMWLoadIntf2DataSelIntf_Create(int arg0) {
    FUN_003c3680();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2DataSelIntf_metaObject, arg0);
}

igMetaObject *beNDMWLoadIntf2DataSelIntf_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2DataSelIntf_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_003c3680();
    return g_beNDMWLoadIntf2DataSelIntf_metaObject;
}

int beNDMWLoadIntf2DataSelIntf_GetVTable(void) {
    union U_3c35f0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0053d0c0[0];
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

void FUN_003c3680(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DataSelIntf_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2DataSelIntf_callbackList[] = { FUN_0034cb30, FUN_003c7090, FUN_003c7830, FUN_003c4f00, FUN_003c6c70, FUN_003c3ac0, 0 };

void *beNDMWLoadIntf2DataSelIntf_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2DataSelIntf_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2DataSelIntf_GetMetaObject,
        "beNDMWLoadIntf2DataSelIntf",
        0x5c, /* instance size */
        beNDMWLoadIntf2DataSelIntf_GetVTable,
        beNDMWLoadIntf2DataSelIntf_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DataSelIntf_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2DataSelIntf_GetMetaObject(void)
{
    beNDMWLoadIntf2DataSelIntf_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2DataSelIntf_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2DataSelIntf_fieldTable[] = {
    "_mcSelPoint",
    "_svDataSelPoint",
    "_padManager",
    "_comMdlCtrl",
    "_textOrder",
    "_commonIntf",
    "_mesWin",
    "_statDisp",
    "_isSaveArea",
    "_isUpStatWin",
    "_isDownStatWin",
    "_isSlotWin",
    "_isSelCur",
    "_kind",
    "_plNo",
    "_mesKind",
    "_result",
    "_isEnd",
    "_isCancel",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2DataSelIntf_fieldHandles[] = {
    &g_beNDMWLoadIntf2DataSelIntf_mcSelPointMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_svDataSelPointMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_padManagerMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_comMdlCtrlMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_textOrderMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_commonIntfMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_mesWinMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_statDispMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isSaveAreaMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isUpStatWinMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isDownStatWinMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isSlotWinMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isSelCurMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_kindMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_plNoMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_mesKindMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_resultMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isEndMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isCancelMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_st0MetaField,
    &g_beNDMWLoadIntf2DataSelIntf_st1MetaField,
    &g_beNDMWLoadIntf2DataSelIntf_st2MetaField,
    &g_beNDMWLoadIntf2DataSelIntf_st3MetaField,
};
static int g_beNDMWLoadIntf2DataSelIntf_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    49,
    50,
    51,
    52,
    56,
    60,
    64,
    68,
    72,
    73,
    76,
    80,
    84,
    88,
};

void beNDMWLoadIntf2DataSelIntf_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    igObjectRefMetaField *temp_s0;
    igObjectRefMetaField *temp_s0_2;
    igObjectRefMetaField *temp_s0_3;
    igObjectRefMetaField *temp_s0_4;
    igObjectRefMetaField *temp_s0_5;
    igObjectRefMetaField *temp_s0_6;
    igMetaObject *temp_s1;
    igStringMetaField *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (igMetaObject *)(g_beNDMWLoadIntf2DataSelIntf_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2DataSelIntf_ctorTable, 0x17);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(temp_s1->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "DATASELINTF");
    temp_v0_2->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2DataSelIntf_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)((int) ((int)temp_v0_2->_refCount - 1));
    if (((unsigned long long) ((long long) (int)temp_v0_2->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    temp_s0->_metaObject = FUN_0034c8e0();
    temp_s0->_refCounted = 0;
    temp_s0_2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    temp_s0_2->_metaObject = (int)FUN_003c6ee0();
    temp_s0_2->_refCounted = 0;
    temp_s0_3 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4));
    temp_s0_3->_metaObject = (int)FUN_003c7700();
    temp_s0_3->_refCounted = 0;
    temp_s0_4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5));
    temp_s0_4->_metaObject = (int)FUN_003c4c20();
    temp_s0_4->_refCounted = 0;
    temp_s0_5 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 6));
    temp_s0_5->_metaObject = (int)FUN_003c6b40();
    temp_s0_5->_refCounted = 0;
    temp_s0_6 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7));
    temp_s0_6->_metaObject = (int)FUN_003c3940();
    temp_s0_6->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2DataSelIntf_fieldTable, g_beNDMWLoadIntf2DataSelIntf_fieldHandles, g_beNDMWLoadIntf2DataSelIntf_fieldOffsets, temp_s2);
}

