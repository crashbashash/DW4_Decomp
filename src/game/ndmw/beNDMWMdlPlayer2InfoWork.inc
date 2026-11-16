igMetaObject *g_beNDMWMdlPlayer2InfoWork_metaObject;
igMetaField *g_beNDMWMdlPlayer2InfoWork_isPowerOnMetaField;
igMetaField *g_beNDMWMdlPlayer2InfoWork_timerCountMetaField;
igMetaField *g_beNDMWMdlPlayer2InfoWork_bitMetaField;
igMetaField *g_beNDMWMdlPlayer2InfoWork_expMetaField;
igMetaEnum *g_beNDMWMdlPlayer2InfoWork_panelCloseSeqListMetaEnum;

void beNDMWMdlPlayer2InfoWork_Create(int allocator) {
    beNDMWMdlPlayer2InfoWork_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlPlayer2InfoWork_metaObject, allocator);
}

void *beNDMWMdlPlayer2InfoWork_ResolveMetaObject(void) {
    bool ok;
    if (g_beNDMWMdlPlayer2InfoWork_metaObject == 0) goto make;
    ok = !!(g_beNDMWMdlPlayer2InfoWork_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWMdlPlayer2InfoWork_EnsureRegistered();
done:;
    return g_beNDMWMdlPlayer2InfoWork_metaObject;
}

int beNDMWMdlPlayer2InfoWork_GetVTable(void) {
    struct W_3bf5f0 o;
    int r;

    beModelCtrlInfoWork_Construct((beModelCtrlInfoWork *)&o);
    o.vt = g_beNDMWMdlPlayer2InfoWork_vtable;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beNDMWMdlPlayer2InfoWork_vtable;
    FUN_00350410(&o, 0);
    return r;
}

void *beModelCtrlInfoWork_Construct(beModelCtrlInfoWork *self) {
    igObject_InitHeader();
    self->_vtable = (int)(&g_beModelCtrlInfoWork_vtable[0]);
    self->_mHp = 0;
    self->_hp = 0;
    self->_seqCodeName = 0;
    self->_comData = 0;
    self->_labelSeqList = 0;
    self->_labelNameList = 0;
    self->_labelOffsetList = 0;
    self->_luaBHit = 0;
    self->_luaWHit = 0;
    self->_luaFHit = 0;
    self->_pdMoveDataList = 0;
    self->_wCheckName = 0;
    self->_aI = 0;
    self->_targetMode = 0;
    self->_targetKind = 0;
    self->_targetSpc1 = 0;
    self->_keyEventName = 0;
    self->_posLockNode = 0;
    self->_posLockTrc = 0;
    self->_posLockModelName = 0;
    self->_posLockBoneName = 0;
    self->_moveObjectList = 0;
    self->_rideOnData = 0;
    self->_debugHitBoxNode = 0;
    self->_hitBody = 0;
    self->_hitParentName = 0;
    self->_subCommand = 0;
    self->_baseAABox = 0;
    return self;
}

void beNDMWMdlPlayer2InfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayer2InfoWork_Register);
}

void *beNDMWMdlPlayer2InfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlPlayer2InfoWork_metaObject,
        beModelCtrlInfoWork_Register,
        beModelCtrlInfoWork_GetPublishedMetaObject,
        beNDMWMdlPlayer2InfoWork_GetMetaObject,
        "beNDMWMdlPlayer2InfoWork",
        0xfc, /* instance size */
        beNDMWMdlPlayer2InfoWork_GetVTable,
        beNDMWMdlPlayer2InfoWork_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlPlayer2InfoWork_GetMetaObject(void)
{
    beNDMWMdlPlayer2InfoWork_ResolveMetaObject();
}

int beModelCtrlInfoWork_GetPublishedMetaObject(void) {
    return g_beModelCtrlInfoWork_metaObject[0];
}

static FieldFactory g_beNDMWMdlPlayer2InfoWork_ctorTable[] = {
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWMdlPlayer2InfoWork_fieldTable[] = {
    "_isPowerOn",
    "_timerCount",
    "_bit",
    "_exp",
};
static igMetaField **g_beNDMWMdlPlayer2InfoWork_fieldHandles[] = {
    &g_beNDMWMdlPlayer2InfoWork_isPowerOnMetaField,
    &g_beNDMWMdlPlayer2InfoWork_timerCountMetaField,
    &g_beNDMWMdlPlayer2InfoWork_bitMetaField,
    &g_beNDMWMdlPlayer2InfoWork_expMetaField,
};
static int g_beNDMWMdlPlayer2InfoWork_fieldOffsets[] = {
    236,
    240,
    244,
    248,
};

void beNDMWMdlPlayer2InfoWork_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWMdlPlayer2InfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWMdlPlayer2InfoWork_ctorTable, 4);
    igMetaObject_NameFields(meta, g_beNDMWMdlPlayer2InfoWork_fieldTable, g_beNDMWMdlPlayer2InfoWork_fieldHandles, g_beNDMWMdlPlayer2InfoWork_fieldOffsets, base);
}

static const char *g_beNDMWMdlPlayer2InfoWork_panelCloseSeqListNames[] = {
    "SQ_SDMG",
    "SQ_MDMG",
    "SQ_LDMG",
    "SQ_DDMG",
    "SQ_DEAD",
    "SQ_SLEP",
    "SQ_STUN",
};
static int g_beNDMWMdlPlayer2InfoWork_panelCloseSeqListValues[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
};

igMetaEnum *PanelCloseSeqList_GetMetaEnum(void) {
    if (g_beNDMWMdlPlayer2InfoWork_panelCloseSeqListMetaEnum == 0) {
        g_beNDMWMdlPlayer2InfoWork_panelCloseSeqListMetaEnum = igMetaEnum_Create("PanelCloseSeqList", g_beNDMWMdlPlayer2InfoWork_panelCloseSeqListNames, g_beNDMWMdlPlayer2InfoWork_panelCloseSeqListValues, 7);
    }
    return g_beNDMWMdlPlayer2InfoWork_panelCloseSeqListMetaEnum;
}

