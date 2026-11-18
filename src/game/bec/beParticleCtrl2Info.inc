igMetaObject *g_beParticleCtrl2Info_metaObject;
igMetaField *g_beParticleCtrl2Info_mainSwitchMetaField;
igMetaField *g_beParticleCtrl2Info_subSwitchMetaField;
igMetaField *g_beParticleCtrl2Info_endTimeFloatMetaField;
igMetaField *g_beParticleCtrl2Info_endTimeLongMetaField;

void *beParticleCtrl2Info_GetMetaObject(void) {
    igMetaObject *g = g_beParticleCtrl2Info_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beParticleCtrl2Info_EnsureRegistered();
    }
    return g_beParticleCtrl2Info_metaObject;
}

int beParticleCtrl2Info_GetVTable(void) {
    beParticleCtrl2Info obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._dataList = 0;
    obj._ramList = 0;
    obj._vtable = (int)&g_beParticleCtrl2Info_vtable[0];
    obj._mainSwitch = 0;
    obj._subSwitch = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beParticleCtrl2Info_vtable[0];
    igSmartPointer_igSwitch_Destruct((igSmartPointer<igObject> *)&obj._subSwitch, -1);
    igSmartPointer_igSwitch_Destruct((igSmartPointer<igObject> *)&obj._mainSwitch, -1);
    beBaseInfo_Destroy((beBaseInfo *)&obj, (short)0);
    return vtable;
}

void beParticleCtrl2Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2Info_Register);
}

static igMetaObjectCallback g_beParticleCtrl2Info_callbackList[] = { igSwitch_EnsureRegistered, 0 };

CallbackArray *beParticleCtrl2Info_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beParticleCtrl2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beParticleCtrl2Info_GetMetaObjectFunction,
        "beParticleCtrl2Info",
        0x30, /* instance size */
        beParticleCtrl2Info_GetVTable,
        beParticleCtrl2Info_InitFields,
        0, /* extra callback item */
        g_beParticleCtrl2Info_callbackList /* callback list */
    );
}

void beParticleCtrl2Info_GetMetaObjectFunction(void)
{
    beParticleCtrl2Info_GetMetaObject();
}

static FieldFactory g_beParticleCtrl2Info_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igLongMetaField_Create,
};
static const char *g_beParticleCtrl2Info_fieldTable[] = {
    "_mainSwitch",
    "_subSwitch",
    "_endTimeFloat",
    "_endTimeLong",
};
static igMetaField **g_beParticleCtrl2Info_fieldHandles[] = {
    &g_beParticleCtrl2Info_mainSwitchMetaField,
    &g_beParticleCtrl2Info_subSwitchMetaField,
    &g_beParticleCtrl2Info_endTimeFloatMetaField,
    &g_beParticleCtrl2Info_endTimeLongMetaField,
};
static int g_beParticleCtrl2Info_fieldOffsets[] = {
    28,
    32,
    36,
    40,
};

void beParticleCtrl2Info_InitFields(void) {
    int base;
    void *subSwitch;
    void *mainSwitch;
    igMetaObject *meta;

    meta = g_beParticleCtrl2Info_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beParticleCtrl2Info_ctorTable, 4);
    mainSwitch = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)mainSwitch)->_metaObject = (int)igSwitch_GetOrCreateMetaObject();
    subSwitch = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)subSwitch)->_metaObject = (int)igSwitch_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beParticleCtrl2Info_fieldTable, g_beParticleCtrl2Info_fieldHandles, g_beParticleCtrl2Info_fieldOffsets, base);
}

igMetaEnum *g_beParticleCtrl2Info_messageMetaEnum;
static const char *g_beParticleCtrl2Info_messageNames[] = {
    "GENERATE", "ISRUN", "SQ_ERAS", "GETSEQNAMELIST",
    "ONCTRL", "OFCTRL", "ONFREEZE", "OFFREEZE",
};
static int g_beParticleCtrl2Info_messageValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
};

igMetaEnum *beParticleCtrl2_GetMessageEnum(void) {
    if (g_beParticleCtrl2Info_messageMetaEnum == 0) {
        g_beParticleCtrl2Info_messageMetaEnum = igMetaEnum_Create("Message", g_beParticleCtrl2Info_messageNames, g_beParticleCtrl2Info_messageValues, 8);
    }
    return g_beParticleCtrl2Info_messageMetaEnum;
}

