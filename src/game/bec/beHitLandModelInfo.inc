igMetaObject *g_beHitLandModelInfo_metaObject;
igMetaField *g_beHitLandModelInfo_switchgraphMetaField;
igMetaField *g_beHitLandModelInfo_checkSwitchMetaField;
igMetaField *g_beHitLandModelInfo_nameListMetaField;
igMetaField *g_beHitLandModelInfo_kindMetaField;

igMetaObject *beHitLandModelInfo_GetMetaObject(void) {
    if (g_beHitLandModelInfo_metaObject == 0 || !isValid(g_beHitLandModelInfo_metaObject)) beHitLandModelInfo_EnsureRegistered();
    return g_beHitLandModelInfo_metaObject;
}

int beHitLandModelInfo_GetVTable(void) {
    struct Obj_35d4f0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.vt = &g_beHitLandModelInfo_vtable[0];
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beHitLandModelInfo_vtable[0];
    FUN_00343260((ObjectRefWord *)&obj.w9, -1);
    FUN_00343260((ObjectRefWord *)&obj.w8, -1);
    igSmartPointer_igObjectList_Destruct(&obj.w7, -1);
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return t;
}

void beHitLandModelInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandModelInfo_Register);
}

static igMetaObjectCallback g_beHitLandModelInfo_callbackList[] = { igSwitch_EnsureRegistered, igObjectList_EnsureRegistered, 0 };

void *beHitLandModelInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandModelInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beHitLandModelInfo_GetMetaObjectFunction,
        "beHitLandModelInfo",
        0x2c, /* instance size */
        beHitLandModelInfo_GetVTable,
        beHitLandModelInfo_InitFields,
        0, /* extra callback item */
        g_beHitLandModelInfo_callbackList /* callback list */
    );
}

void beHitLandModelInfo_GetMetaObjectFunction(void)
{
    beHitLandModelInfo_GetMetaObject();
}

static FieldFactory g_beHitLandModelInfo_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beHitLandModelInfo_fieldTable[] = {
    "_switchgraph",
    "_checkSwitch",
    "_nameList",
    "_kind",
};
static igMetaField **g_beHitLandModelInfo_fieldHandles[] = {
    &g_beHitLandModelInfo_switchgraphMetaField,
    &g_beHitLandModelInfo_checkSwitchMetaField,
    &g_beHitLandModelInfo_nameListMetaField,
    &g_beHitLandModelInfo_kindMetaField,
};
static int g_beHitLandModelInfo_fieldOffsets[] = {
    32,
    36,
    28,
    40,
};

void beHitLandModelInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beHitLandModelInfo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beHitLandModelInfo_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igSwitch_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igSwitch_GetOrCreateMetaObject();
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beHitLandModelInfo_fieldTable, g_beHitLandModelInfo_fieldHandles, g_beHitLandModelInfo_fieldOffsets, temp_s2);
}

igMetaEnum *g_beHitLandModelInfo_messageMetaEnum;
static const char *g_beHitLandModelInfo_messageNames[] = {
    "CHECKWALL", "CHECKWALLFULL", "CHECKLAND", "ONHIT",
    "OFFHIT",
};
static int g_beHitLandModelInfo_messageValues[] = {
    0, 1, 2, 3, 4,
};

igMetaEnum *FUN_0035d720(void) {
    if (g_beHitLandModelInfo_messageMetaEnum == 0) {
        g_beHitLandModelInfo_messageMetaEnum = igMetaEnum_Create("Message", g_beHitLandModelInfo_messageNames, g_beHitLandModelInfo_messageValues, 5);
    }
    return g_beHitLandModelInfo_messageMetaEnum;
}

