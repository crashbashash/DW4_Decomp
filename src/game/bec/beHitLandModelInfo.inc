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
    beHitLandModelInfo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beHitLandModelInfo_vtable[0];
    obj._nameList = 0;
    obj._switchgraph = 0;
    obj._checkSwitch = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beHitLandModelInfo_vtable[0];
    igSmartPointer_igSwitch_Destruct((igSmartPointer<igObject> *)&obj._checkSwitch, -1);
    igSmartPointer_igSwitch_Destruct((igSmartPointer<igObject> *)&obj._switchgraph, -1);
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)&obj._nameList, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beHitLandModelInfo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandModelInfo_Register);
}

static igMetaObjectCallback g_beHitLandModelInfo_callbackList[] = { igSwitch_EnsureRegistered, igObjectList_EnsureRegistered, 0 };

CallbackArray *beHitLandModelInfo_Register(void) {
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
    int base;
    void *nameList;
    void *checkSwitch;
    void *switchgraph;
    igMetaObject *meta;

    meta = g_beHitLandModelInfo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beHitLandModelInfo_ctorTable, 4);
    switchgraph = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)switchgraph)->_metaObject = (int)igSwitch_GetOrCreateMetaObject();
    checkSwitch = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)checkSwitch)->_metaObject = (int)igSwitch_GetOrCreateMetaObject();
    nameList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)nameList)->_metaObject = (int)igObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beHitLandModelInfo_fieldTable, g_beHitLandModelInfo_fieldHandles, g_beHitLandModelInfo_fieldOffsets, base);
}

igMetaEnum *g_beHitLandModelInfo_messageMetaEnum;
static const char *g_beHitLandModelInfo_messageNames[] = {
    "CHECKWALL", "CHECKWALLFULL", "CHECKLAND", "ONHIT",
    "OFFHIT",
};
static int g_beHitLandModelInfo_messageValues[] = {
    0, 1, 2, 3, 4,
};

igMetaEnum *beHitLandModel_GetMessageEnum(void) {
    if (g_beHitLandModelInfo_messageMetaEnum == 0) {
        g_beHitLandModelInfo_messageMetaEnum = igMetaEnum_Create("Message", g_beHitLandModelInfo_messageNames, g_beHitLandModelInfo_messageValues, 5);
    }
    return g_beHitLandModelInfo_messageMetaEnum;
}

