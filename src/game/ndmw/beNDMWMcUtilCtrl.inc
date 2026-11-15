igMetaObject *g_beNDMWMcUtilCtrl_metaObject;
igMetaField *g_beNDMWMcUtilCtrl_messengerMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isUseUtilMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isRdyMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isRunMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isMtapMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isFormatRunMetaField;
igMetaField *g_beNDMWMcUtilCtrl_tgConMetaField;
igMetaField *g_beNDMWMcUtilCtrl_usePlNoMetaField;
igMetaField *g_beNDMWMcUtilCtrl_kindMetaField;
igMetaField *g_beNDMWMcUtilCtrl_resultMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isResultMetaField;
igMetaField *g_beNDMWMcUtilCtrl_svDataMetaField;
igMetaField *g_beNDMWMcUtilCtrl_slotMetaField;
igMetaField *g_beNDMWMcUtilCtrl_st0MetaField;
igMetaField *g_beNDMWMcUtilCtrl_st1MetaField;
igMetaField *g_beNDMWMcUtilCtrl_st2MetaField;
igMetaField *g_beNDMWMcUtilCtrl_st3MetaField;

void FUN_003c51c0(int arg0) {
    FUN_003c5380();
    igMetaObject_CreateInstance(g_beNDMWMcUtilCtrl_metaObject, arg0);
}

igMetaObject *FUN_003c5200(void) {
    if (g_beNDMWMcUtilCtrl_metaObject == 0) {
        g_beNDMWMcUtilCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMcUtilCtrl_metaObject;
}

void *beNDMWMcUtilCtrl_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWMcUtilCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c5380();
    }
    return g_beNDMWMcUtilCtrl_metaObject;
}

int beNDMWMcUtilCtrl_GetVTable(void) {
    beNDMWMcUtilCtrl obj;
    igObject *o;
    int t;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &DAT_0053cda0[0];
    obj._svData = 0;
    obj._slot = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &DAT_0053cda0[0];
    if (&obj._slot != 0) {
        o = (igObject *)obj._slot;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (&obj._svData != 0) {
        o = (igObject *)obj._svData;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void FUN_003c5380(void)
{
    igMetaObject_RunStaticInit(beNDMWMcUtilCtrl_Register);
}

static igMetaObjectCallback g_beNDMWMcUtilCtrl_callbackList[] = { FUN_00357d10, FUN_0034af90, FUN_003c59f0, 0 };

void *beNDMWMcUtilCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMcUtilCtrl_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWMcUtilCtrl_GetMetaObject,
        "beNDMWMcUtilCtrl",
        0x40, /* instance size */
        beNDMWMcUtilCtrl_GetVTable,
        beNDMWMcUtilCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWMcUtilCtrl_callbackList /* callback list */
    );
}

void beNDMWMcUtilCtrl_GetMetaObject(void)
{
    beNDMWMcUtilCtrl_ResolveMetaObject();
}

static FieldFactory g_beNDMWMcUtilCtrl_ctorTable[] = {
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
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWMcUtilCtrl_fieldTable[] = {
    "_messenger",
    "_isUseUtil",
    "_isRdy",
    "_isRun",
    "_isMtap",
    "_isFormatRun",
    "_tgCon",
    "_usePlNo",
    "_kind",
    "_result",
    "_isResult",
    "_svData",
    "_slot",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWMcUtilCtrl_fieldHandles[] = {
    &g_beNDMWMcUtilCtrl_messengerMetaField,
    &g_beNDMWMcUtilCtrl_isUseUtilMetaField,
    &g_beNDMWMcUtilCtrl_isRdyMetaField,
    &g_beNDMWMcUtilCtrl_isRunMetaField,
    &g_beNDMWMcUtilCtrl_isMtapMetaField,
    &g_beNDMWMcUtilCtrl_isFormatRunMetaField,
    &g_beNDMWMcUtilCtrl_tgConMetaField,
    &g_beNDMWMcUtilCtrl_usePlNoMetaField,
    &g_beNDMWMcUtilCtrl_kindMetaField,
    &g_beNDMWMcUtilCtrl_resultMetaField,
    &g_beNDMWMcUtilCtrl_isResultMetaField,
    &g_beNDMWMcUtilCtrl_svDataMetaField,
    &g_beNDMWMcUtilCtrl_slotMetaField,
    &g_beNDMWMcUtilCtrl_st0MetaField,
    &g_beNDMWMcUtilCtrl_st1MetaField,
    &g_beNDMWMcUtilCtrl_st2MetaField,
    &g_beNDMWMcUtilCtrl_st3MetaField,
};
static int g_beNDMWMcUtilCtrl_fieldOffsets[] = {
    8,
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
    52,
    56,
    60,
};

void beNDMWMcUtilCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWMcUtilCtrl_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWMcUtilCtrl_ctorTable, 0x11);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xB));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_0034aeb0();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 0xC));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_003c5910();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNDMWMcUtilCtrl_fieldTable, g_beNDMWMcUtilCtrl_fieldHandles, g_beNDMWMcUtilCtrl_fieldOffsets, temp_s2);
}

