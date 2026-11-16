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
    struct Obj_34c3d0 o;
    int r;

    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f14 = 0;
    o.f18 = 0;
    o.vt = &g_beParticleCtrl2Info_vtable[0];
    o.f1c = 0;
    o.f20 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beParticleCtrl2Info_vtable[0];
    FUN_00343260((ObjectRefWord *)&o.f20, -1);
    FUN_00343260((ObjectRefWord *)&o.f1c, -1);
    FUN_0033ec80((struct S_33ec80 *)&o, (short)0);
    return r;
}

void beParticleCtrl2Info_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2Info_Register);
}

static igMetaObjectCallback g_beParticleCtrl2Info_callbackList[] = { igSwitch_EnsureRegistered, 0 };

void *beParticleCtrl2Info_Register(void) {
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
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beParticleCtrl2Info_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beParticleCtrl2Info_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igSwitch_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igSwitch_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beParticleCtrl2Info_fieldTable, g_beParticleCtrl2Info_fieldHandles, g_beParticleCtrl2Info_fieldOffsets, temp_s2);
}

igMetaEnum *g_beParticleCtrl2Info_messageMetaEnum;
static const char *g_beParticleCtrl2Info_messageNames[] = {
    "GENERATE", "ISRUN", "SQ_ERAS", "GETSEQNAMELIST",
    "ONCTRL", "OFCTRL", "ONFREEZE", "OFFREEZE",
};
static int g_beParticleCtrl2Info_messageValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
};

igMetaEnum *FUN_0034c5d0(void) {
    if (g_beParticleCtrl2Info_messageMetaEnum == 0) {
        g_beParticleCtrl2Info_messageMetaEnum = igMetaEnum_Create("Message", g_beParticleCtrl2Info_messageNames, g_beParticleCtrl2Info_messageValues, 8);
    }
    return g_beParticleCtrl2Info_messageMetaEnum;
}

