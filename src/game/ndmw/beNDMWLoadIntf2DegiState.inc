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

void beNDMWLoadIntf2DegiState_Create(int allocator) {
    beNDMWLoadIntf2DegiState_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2DegiState_metaObject, allocator);
}

void *beNDMWLoadIntf2DegiState_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2DegiState_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLoadIntf2DegiState_EnsureRegistered();
    }
    return g_beNDMWLoadIntf2DegiState_metaObject;
}

int beNDMWLoadIntf2DegiState_GetVTable(void) {
    struct Obj_3c3ed0 o;
    igObject_InitHeader(&o);
    o.vt = &g_beNDMWLoadIntf2DegiState_vtable[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNDMWLoadIntf2DegiState_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DegiState_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2DegiState_callbackList[] = { beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered, beNDMWLoadIntf2TextOrder_EnsureRegistered, beNDMWLoadCtrl2CommonIntf_EnsureRegistered, beMessenger_EnsureRegistered, 0 };

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
    int base;
    void *messenger;
    void *commonIntf;
    void *textOrder;
    void *comMdlCtrl;
    igMetaObject *meta;

    meta = g_beNDMWLoadIntf2DegiState_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWLoadIntf2DegiState_ctorTable, 0x10);
    comMdlCtrl = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)comMdlCtrl)->_metaObject = (int)beNDMWLoadIntf2ComMdlCtrl_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)comMdlCtrl)->_refCounted = 0;
    textOrder = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)textOrder)->_metaObject = (int)beNDMWLoadIntf2TextOrder_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)textOrder)->_refCounted = 0;
    commonIntf = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)commonIntf)->_metaObject = (int)beNDMWLoadCtrl2CommonIntf_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)commonIntf)->_refCounted = 0;
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)messenger)->_metaObject = beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beNDMWLoadIntf2DegiState_fieldTable, g_beNDMWLoadIntf2DegiState_fieldHandles, g_beNDMWLoadIntf2DegiState_fieldOffsets, base);
}

