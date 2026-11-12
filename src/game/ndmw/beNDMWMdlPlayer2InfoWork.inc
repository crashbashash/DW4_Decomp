void FUN_003bf560(int arg0) {
    FUN_003bf700();
    igMetaObject_CreateInstance(*(int *)0x58B378, arg0);
}

void *beNDMWMdlPlayer2InfoWork_ResolveMetaObject(void) {
    bool ok;
    if (g_beNDMWMdlPlayer2InfoWork_metaObject[0] == 0) goto make;
    ok = !!(g_beNDMWMdlPlayer2InfoWork_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_003bf700();
done:;
    return g_beNDMWMdlPlayer2InfoWork_metaObject[0];
}

int beNDMWMdlPlayer2InfoWork_GetVTable(void) {
    struct W_3bf5f0 o;
    int r;

    beModelCtrlInfoWork_Construct((beModelCtrlInfoWork *)&o);
    o.vt = DAT_0053d500;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053d500;
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

void FUN_003bf700(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayer2InfoWork_Register);
}

void *beNDMWMdlPlayer2InfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlPlayer2InfoWork_metaObject,
        beModelCtrlInfoWork_Register,
        beModelCtrlInfoWork_GetPublishedMetaObject,
        beNDMWMdlPlayer2InfoWork_GetMetaObject,
        beNDMWMdlPlayer2InfoWork_className,
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

int FUN_003bf7b0(void) {
    return g_beModelCtrlInfoWork_metaObject[0];
}

void beNDMWMdlPlayer2InfoWork_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWMdlPlayer2InfoWork_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004ca7e0[0], 4);
    igMetaObject_NameFields(temp_s0, &DAT_004ca7f0[0], &DAT_004ca800[0], &DAT_004ca810[0], temp_s1);
}

int FUN_003bf830(void) {
    if (DAT_0058b3a0[0] == 0) {
        DAT_0058b3a0[0] = igMetaEnum_Create(&DAT_00512120[0], &DAT_004ca820[0], &DAT_004ca840[0], 7);
    }
    return DAT_0058b3a0[0];
}

