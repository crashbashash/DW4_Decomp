igMetaObject *g_beNDMWLoadIntf2NameSel_metaObject;
int g_beNDMWLoadIntf2NameSel_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2NameSel_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_comMdlCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_textOrderMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_ramNoMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_selDataNoMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_langIDMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_tateMaxMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_tateMinMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_tatePointMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_yokoPointMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_yokoCurPosMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_oldPadDataMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_nameMojiMaxMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_nameCurPosMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isEndMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isMakeNameMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isQuestionMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isAnswerMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isNameOKMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isSideCurMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_st0MetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_st1MetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_st2MetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_st3MetaField;

void beNDMWLoadIntf2NameSel_Create(int arg0) {
    FUN_003c28e0();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2NameSel_metaObject, arg0);
}

void *beNDMWLoadIntf2NameSel_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2NameSel_metaObject;
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (exceptions on); `if (ready = ...)` folds it away */
        ready = g->_validity & 4;
        if (ready != false) goto end;
    }
    FUN_003c28e0();
end:
    return g_beNDMWLoadIntf2NameSel_metaObject;
}

int beNDMWLoadIntf2NameSel_GetVTable(void) {
    union U_3c2850 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_0053d240[0];
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

void FUN_003c28e0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2NameSel_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2NameSel_callbackList[] = { FUN_00357d10, FUN_0034cb30, FUN_003c7090, FUN_003c7830, 0 };

void *beNDMWLoadIntf2NameSel_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2NameSel_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2NameSel_GetMetaObject,
        "beNDMWLoadIntf2NameSel",
        0x120, /* instance size */
        beNDMWLoadIntf2NameSel_GetVTable,
        beNDMWLoadIntf2NameSel_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2NameSel_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2NameSel_GetMetaObject(void)
{
    beNDMWLoadIntf2NameSel_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2NameSel_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2NameSel_fieldTable[] = {
    "_messenger",
    "_padManager",
    "_comMdlCtrl",
    "_textOrder",
    "_ramNo",
    "_selDataNo",
    "_langID",
    "_tateMax",
    "_tateMin",
    "_tatePoint",
    "_yokoPoint",
    "_yokoCurPos",
    "_oldPadData",
    "_nameMojiMax",
    "_nameCurPos",
    "_isEnd",
    "_isMakeName",
    "_isQuestion",
    "_isAnswer",
    "_isNameOK",
    "_isSideCur",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2NameSel_fieldHandles[] = {
    &g_beNDMWLoadIntf2NameSel_messengerMetaField,
    &g_beNDMWLoadIntf2NameSel_padManagerMetaField,
    &g_beNDMWLoadIntf2NameSel_comMdlCtrlMetaField,
    &g_beNDMWLoadIntf2NameSel_textOrderMetaField,
    &g_beNDMWLoadIntf2NameSel_ramNoMetaField,
    &g_beNDMWLoadIntf2NameSel_selDataNoMetaField,
    &g_beNDMWLoadIntf2NameSel_langIDMetaField,
    &g_beNDMWLoadIntf2NameSel_tateMaxMetaField,
    &g_beNDMWLoadIntf2NameSel_tateMinMetaField,
    &g_beNDMWLoadIntf2NameSel_tatePointMetaField,
    &g_beNDMWLoadIntf2NameSel_yokoPointMetaField,
    &g_beNDMWLoadIntf2NameSel_yokoCurPosMetaField,
    &g_beNDMWLoadIntf2NameSel_oldPadDataMetaField,
    &g_beNDMWLoadIntf2NameSel_nameMojiMaxMetaField,
    &g_beNDMWLoadIntf2NameSel_nameCurPosMetaField,
    &g_beNDMWLoadIntf2NameSel_isEndMetaField,
    &g_beNDMWLoadIntf2NameSel_isMakeNameMetaField,
    &g_beNDMWLoadIntf2NameSel_isQuestionMetaField,
    &g_beNDMWLoadIntf2NameSel_isAnswerMetaField,
    &g_beNDMWLoadIntf2NameSel_isNameOKMetaField,
    &g_beNDMWLoadIntf2NameSel_isSideCurMetaField,
    &g_beNDMWLoadIntf2NameSel_st0MetaField,
    &g_beNDMWLoadIntf2NameSel_st1MetaField,
    &g_beNDMWLoadIntf2NameSel_st2MetaField,
    &g_beNDMWLoadIntf2NameSel_st3MetaField,
};
static int g_beNDMWLoadIntf2NameSel_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
    76,
    77,
    78,
    79,
    80,
    81,
    84,
    88,
    92,
    96,
};

void beNDMWLoadIntf2NameSel_InitFields(void) {
    int temp_s2;
    int temp_s3;
    void **temp_v0;
    void *temp_s0;
    void *temp_s0_2;
    void *temp_s0_3;
    void *temp_s0_4;
    void *temp_s1;
    igStringMetaField *temp_v0_2;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)(g_beNDMWLoadIntf2NameSel_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2NameSel_ctorTable, 0x19);
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_name"));
    temp_s3 = ObjectPointerList_FindIndex(((igMetaObject *)temp_s1)->_metaFields, temp_v0);
    temp_v0_2 = (igStringMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    igStringMetaField_SetDefaultText(temp_v0_2, "NAMESEL");
    temp_v0_2->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2NameSel_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = temp_v0_2->_refCount - 1;
    if (((unsigned long long)(long long)temp_v0_2->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    ((igObjectRefMetaField *)temp_s0)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s0)->_refCounted = 0;
    temp_s0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s0_2)->_metaObject = FUN_0034c8e0();
    ((igObjectRefMetaField *)temp_s0_2)->_refCounted = 0;
    temp_s0_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s0_3)->_metaObject = (int)FUN_003c6ee0();
    ((igObjectRefMetaField *)temp_s0_3)->_refCounted = 0;
    temp_s0_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s0_4)->_metaObject = (int)FUN_003c7700();
    ((igObjectRefMetaField *)temp_s0_4)->_refCounted = 0;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 0xE), -1);
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWLoadIntf2NameSel_fieldTable, g_beNDMWLoadIntf2NameSel_fieldHandles, g_beNDMWLoadIntf2NameSel_fieldOffsets, temp_s2);
}

