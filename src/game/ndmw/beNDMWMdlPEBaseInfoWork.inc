igMetaObject *g_beNDMWMdlPEBaseInfoWork_metaObject;
igMetaField *g_beNDMWMdlPEBaseInfoWork_isPlayerMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_dispRamNoListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_dispPosNoListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_timerListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_isFirstListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_poisonDamageMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_poisonEnduranceMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_downDataListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_upDataListMetaField;
igMetaField *g_beNDMWMdlPEBaseInfoWork_messengerMetaField;

void *beNDMWMdlPEBaseInfoWork_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlPEBaseInfoWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlPEBaseInfoWork_EnsureRegistered();
    }
    return g_beNDMWMdlPEBaseInfoWork_metaObject;
}

int beNDMWMdlPEBaseInfoWork_GetVTable(void) {
    PEBaseInfoWorkObj work;
    return *(int *)((char *)&work + *(int *)((char *)g_objectSystem[0] + 916));
}

int *FUN_003c0760(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void beNDMWMdlPEBaseInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPEBaseInfoWork_Register);
}

static igMetaObjectCallback g_beNDMWMdlPEBaseInfoWork_callbackList[] = { igIntList_EnsureRegistered, igBoolList_EnsureRegistered, beMessenger_EnsureRegistered, 0 };

void *beNDMWMdlPEBaseInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlPEBaseInfoWork_metaObject,
        beModelCtrlInfoWork_Register,
        beModelCtrlInfoWork_GetPublishedMetaObject,
        beNDMWMdlPEBaseInfoWork_GetMetaObject,
        "beNDMWMdlPEBaseInfoWork",
        0x114, /* instance size */
        beNDMWMdlPEBaseInfoWork_GetVTable,
        beNDMWMdlPEBaseInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPEBaseInfoWork_callbackList /* callback list */
    );
}

void beNDMWMdlPEBaseInfoWork_GetMetaObject(void)
{
    beNDMWMdlPEBaseInfoWork_ResolveMetaObject();
}

static FieldFactory g_beNDMWMdlPEBaseInfoWork_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWMdlPEBaseInfoWork_fieldTable[] = {
    "_isPlayer",
    "_dispRamNoList",
    "_dispPosNoList",
    "_timerList",
    "_isFirstList",
    "_poisonDamage",
    "_poisonEndurance",
    "_downDataList",
    "_upDataList",
    "_messenger",
};
static igMetaField **g_beNDMWMdlPEBaseInfoWork_fieldHandles[] = {
    &g_beNDMWMdlPEBaseInfoWork_isPlayerMetaField,
    &g_beNDMWMdlPEBaseInfoWork_dispRamNoListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_dispPosNoListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_timerListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_isFirstListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_poisonDamageMetaField,
    &g_beNDMWMdlPEBaseInfoWork_poisonEnduranceMetaField,
    &g_beNDMWMdlPEBaseInfoWork_downDataListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_upDataListMetaField,
    &g_beNDMWMdlPEBaseInfoWork_messengerMetaField,
};
static int g_beNDMWMdlPEBaseInfoWork_fieldOffsets[] = {
    236,
    240,
    244,
    248,
    252,
    256,
    260,
    264,
    268,
    272,
};

void beNDMWMdlPEBaseInfoWork_InitFields(void) {
    void *temp_s2_7;
    void *temp_s2_6;
    void *temp_s2_5;
    void *temp_s2_4;
    void *temp_s2_3;
    void *temp_s2_2;
    void *temp_s2;
    void *temp_s1;
    int temp_s0;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)g_beNDMWMdlPEBaseInfoWork_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWMdlPEBaseInfoWork_ctorTable, 0xA);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = igBoolList_GetOrCreateMetaObject();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_7)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWMdlPEBaseInfoWork_fieldTable, g_beNDMWMdlPEBaseInfoWork_fieldHandles, g_beNDMWMdlPEBaseInfoWork_fieldOffsets, temp_s0);
}

