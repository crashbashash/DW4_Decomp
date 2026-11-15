igMetaObject *g_beNDMWLoadIntf2DegiState_metaObject;
igMetaField *g_beNDMWLoadIntf2DegiState_comMdlCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_textOrderMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_commonIntfMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_plNoMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_dispPosMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_isEndMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_isAnmEndMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_closeKindMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_kindMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_dataNoMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_isUseDataMetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_st0MetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_st1MetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_st2MetaField;
igMetaField *g_beNDMWLoadIntf2DegiState_st3MetaField;

void beNDMWLoadIntf2DegiState_Create(int arg0) {
    FUN_003c3f10();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2DegiState_metaObject, arg0);
}

void *beNDMWLoadIntf2DegiState_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2DegiState_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c3f10();
    }
    return g_beNDMWLoadIntf2DegiState_metaObject;
}

int beNDMWLoadIntf2DegiState_GetVTable(void) {
    struct Obj_3c3ed0 o;
    igObject_InitHeader(&o);
    o.vt = &DAT_0053cf90[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c3f10(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DegiState_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2DegiState_callbackList[] = { FUN_003c7090, FUN_003c7830, FUN_003c4f00, FUN_00357d10, 0 };

void *beNDMWLoadIntf2DegiState_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2DegiState_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWLoadIntf2DegiState_GetMetaObject,
        "beNDMWLoadIntf2DegiState",
        0x44, /* instance size */
        beNDMWLoadIntf2DegiState_GetVTable,
        beNDMWLoadIntf2DegiState_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DegiState_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2DegiState_GetMetaObject(void)
{
    beNDMWLoadIntf2DegiState_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2DegiState_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2DegiState_fieldTable[] = {
    "_comMdlCtrl",
    "_textOrder",
    "_commonIntf",
    "_messenger",
    "_plNo",
    "_dispPos",
    "_isEnd",
    "_isAnmEnd",
    "_closeKind",
    "_kind",
    "_dataNo",
    "_isUseData",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2DegiState_fieldHandles[] = {
    &g_beNDMWLoadIntf2DegiState_comMdlCtrlMetaField,
    &g_beNDMWLoadIntf2DegiState_textOrderMetaField,
    &g_beNDMWLoadIntf2DegiState_commonIntfMetaField,
    &g_beNDMWLoadIntf2DegiState_messengerMetaField,
    &g_beNDMWLoadIntf2DegiState_plNoMetaField,
    &g_beNDMWLoadIntf2DegiState_dispPosMetaField,
    &g_beNDMWLoadIntf2DegiState_isEndMetaField,
    &g_beNDMWLoadIntf2DegiState_isAnmEndMetaField,
    &g_beNDMWLoadIntf2DegiState_closeKindMetaField,
    &g_beNDMWLoadIntf2DegiState_kindMetaField,
    &g_beNDMWLoadIntf2DegiState_dataNoMetaField,
    &g_beNDMWLoadIntf2DegiState_isUseDataMetaField,
    &g_beNDMWLoadIntf2DegiState_st0MetaField,
    &g_beNDMWLoadIntf2DegiState_st1MetaField,
    &g_beNDMWLoadIntf2DegiState_st2MetaField,
    &g_beNDMWLoadIntf2DegiState_st3MetaField,
};
static int g_beNDMWLoadIntf2DegiState_fieldOffsets[] = {
    12,
    16,
    20,
    8,
    24,
    28,
    32,
    33,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
};

void beNDMWLoadIntf2DegiState_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWLoadIntf2DegiState_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWLoadIntf2DegiState_ctorTable, 0x10);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c6ee0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_003c7700();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_003c4c20();
    ((igObjectRefMetaField *)temp_s1_3)->_refCounted = 0;
    temp_s1_4 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s1_4)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, g_beNDMWLoadIntf2DegiState_fieldTable, g_beNDMWLoadIntf2DegiState_fieldHandles, g_beNDMWLoadIntf2DegiState_fieldOffsets, temp_s2);
}

