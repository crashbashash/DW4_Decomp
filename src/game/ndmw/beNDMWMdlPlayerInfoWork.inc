igMetaObject *g_beNDMWMdlPlayerInfoWork_metaObject;
igMetaField *g_beNDMWMdlPlayerInfoWork_turnAtkTimerMetaField;
igMetaField *g_beNDMWMdlPlayerInfoWork_bodyAtkSt0MetaField;
igMetaField *g_beNDMWMdlPlayerInfoWork_bodyAtkPadMetaField;
igMetaField *g_beNDMWMdlPlayerInfoWork_bodyAtkTimerMetaField;
igMetaField *g_beNDMWMdlPlayerInfoWork_isPanelMetaField;
igMetaField *g_beNDMWMdlPlayerInfoWork_isMainLobbyMetaField;
igMetaField *g_beNDMWMdlPlayerInfoWork_wCheckStMetaField;
igMetaField *g_beNDMWMdlPlayerInfoWork_wCheckModeMetaField;
igMetaEnum *g_beNDMWMdlPlayerInfoWork_damageSeqMetaEnum;
igMetaEnum *g_beNDMWMdlPlayerInfoWork_statusNameMetaEnum;
igMetaEnum *g_beNDMWMdlPlayerInfoWork_msgActionMetaEnum;

beNDMWMdlPlayerInfoWork *beNDMWMdlPlayerInfoWork_Create(int allocator) {
    beNDMWMdlPlayerInfoWork_EnsureRegistered();
    return (beNDMWMdlPlayerInfoWork *)igMetaObject_CreateInstance(g_beNDMWMdlPlayerInfoWork_metaObject, allocator);
}

igMetaObject *beNDMWMdlPlayerInfoWork_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlPlayerInfoWork_metaObject == 0) {
        g_beNDMWMdlPlayerInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlPlayerInfoWork_metaObject;
}

igMetaObject *beNDMWMdlPlayerInfoWork_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWMdlPlayerInfoWork_metaObject != 0) {
        ready = (g_beNDMWMdlPlayerInfoWork_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    beNDMWMdlPlayerInfoWork_EnsureRegistered();
done:
    return g_beNDMWMdlPlayerInfoWork_metaObject;
}

int beNDMWMdlPlayerInfoWork_GetVTable(void) {
    PlayerInfoWorkView work;
    return *(int *)((char *)&work + *(int *)((char *)g_objectSystem[0] + 916));
}

beNDMWMdlPEBaseInfoWork *beNDMWMdlPEBaseInfoWork_Destroy(beNDMWMdlPEBaseInfoWork *self, short flags) {
    if (self) {
        *(int **)&self->_vtable = g_beNDMWMdlPEBaseInfoWork_vtable;
        if (&self->_upDataList != 0) {
            igRelease((igObject *)self->_upDataList);
        }
        if (&self->_downDataList != 0) {
            igRelease((igObject *)self->_downDataList);
        }
        if (&self->_isFirstList != 0) {
            igRelease((igObject *)self->_isFirstList);
        }
        if (&self->_timerList != 0) {
            igRelease((igObject *)self->_timerList);
        }
        if (&self->_dispPosNoList != 0) {
            igRelease((igObject *)self->_dispPosNoList);
        }
        if (&self->_dispRamNoList != 0) {
            igRelease((igObject *)self->_dispRamNoList);
        }
        if (self) {
            *(int **)&self->_vtable = g_beModelCtrlInfoWork_vtable;
            igSmartPointer_igAABox_Destruct(&self->_baseAABox, -1);
            igSmartPointer_beModelCtrlSubCom_Destruct(&self->_subCommand, -1);
            igStringRef_Destruct(&self->_hitParentName, -1);
            igSmartPointer_beModelCtrlInfoHitBody_Destruct(&self->_hitBody, -1);
            igSmartPointer_igGroup_Destruct(&self->_debugHitBoxNode, -1);
            igSmartPointer_beModelCtrlInfoRideOn_Destruct(&self->_rideOnData, -1);
            igSmartPointer_beModelCtrlMoveObjectList_Destruct(&self->_moveObjectList, -1);
            igStringRef_Destruct(&self->_posLockBoneName, -1);
            igStringRef_Destruct(&self->_posLockModelName, -1);
            igSmartPointer_beModelCtrlInfoDataTrc_Destruct(&self->_posLockTrc, -1);
            igSmartPointer_beModelCtrlNode2_Destruct(&self->_posLockNode, -1);
            igStringRef_Destruct(&self->_keyEventName, -1);
            igStringRef_Destruct(&self->_targetSpc1, -1);
            igStringRef_Destruct(&self->_targetKind, -1);
            igStringRef_Destruct(&self->_targetMode, -1);
            igSmartPointer_beModelCtrlInfoAI_Destruct(&self->_aI, -1);
            igStringRef_Destruct(&self->_wCheckName, -1);
            igSmartPointer_igFloatList_Destruct(&self->_pdMoveDataList, -1);
            igStringRef_Destruct(&self->_luaFHit, -1);
            igStringRef_Destruct(&self->_luaWHit, -1);
            igStringRef_Destruct(&self->_luaBHit, -1);
            igSmartPointer_igIntList_Destruct(&self->_labelOffsetList, -1);
            igSmartPointer_igStringRefList_Destruct(&self->_labelNameList, -1);
            igSmartPointer_igStringRefList_Destruct(&self->_labelSeqList, -1);
            igSmartPointer_beModelCtrlData_Destruct(&self->_comData, -1);
            igStringRef_Destruct(&self->_seqCodeName, -1);
            igSmartPointer_beDataObjInt_Destruct(&self->_hp, -1);
            igSmartPointer_beDataObjInt_Destruct(&self->_mHp, -1);
        }
        if (flags > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

PEBaseInfoWorkView::PEBaseInfoWorkView() {
    vtable = g_beNDMWMdlPEBaseInfoWork_vtable;
    dispRamNoList = 0;
    dispPosNoList = 0;
    timerList = 0;
    isFirstList = 0;
    downDataList = 0;
    upDataList = 0;
}

void beNDMWMdlPlayerInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPlayerInfoWork_Register);
}

static igMetaObjectCallback g_beNDMWMdlPlayerInfoWork_callbackList[] = { igIntList_EnsureRegistered, 0 };

void *beNDMWMdlPlayerInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlPlayerInfoWork_metaObject,
        beNDMWMdlPEBaseInfoWork_Register,
        beNDMWMdlPEBaseInfoWork_GetPublishedMetaObject,
        beNDMWMdlPlayerInfoWork_GetMetaObject,
        "beNDMWMdlPlayerInfoWork",
        0x130, /* instance size */
        beNDMWMdlPlayerInfoWork_GetVTable,
        beNDMWMdlPlayerInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPlayerInfoWork_callbackList /* callback list */
    );
}

void beNDMWMdlPlayerInfoWork_GetMetaObject(void)
{
    beNDMWMdlPlayerInfoWork_ResolveMetaObject();
}

igMetaObject *beNDMWMdlPEBaseInfoWork_GetPublishedMetaObject(void) {
    return g_beNDMWMdlPEBaseInfoWork_metaObject;
}

static FieldFactory g_beNDMWMdlPlayerInfoWork_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWMdlPlayerInfoWork_fieldTable[] = {
    "_turnAtkTimer",
    "_bodyAtkSt0",
    "_bodyAtkPad",
    "_bodyAtkTimer",
    "_isPanel",
    "_isMainLobby",
    "_wCheckSt",
    "_wCheckMode",
};
static igMetaField **g_beNDMWMdlPlayerInfoWork_fieldHandles[] = {
    &g_beNDMWMdlPlayerInfoWork_turnAtkTimerMetaField,
    &g_beNDMWMdlPlayerInfoWork_bodyAtkSt0MetaField,
    &g_beNDMWMdlPlayerInfoWork_bodyAtkPadMetaField,
    &g_beNDMWMdlPlayerInfoWork_bodyAtkTimerMetaField,
    &g_beNDMWMdlPlayerInfoWork_isPanelMetaField,
    &g_beNDMWMdlPlayerInfoWork_isMainLobbyMetaField,
    &g_beNDMWMdlPlayerInfoWork_wCheckStMetaField,
    &g_beNDMWMdlPlayerInfoWork_wCheckModeMetaField,
};
static int g_beNDMWMdlPlayerInfoWork_fieldOffsets[] = {
    276,
    280,
    284,
    288,
    292,
    293,
    296,
    300,
};

void beNDMWMdlPlayerInfoWork_InitFields(void) {
    int base;
    void *turnAtkTimer;
    igMetaObject *meta;

    meta = g_beNDMWMdlPlayerInfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWMdlPlayerInfoWork_ctorTable, 8);
    turnAtkTimer = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)turnAtkTimer)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWMdlPlayerInfoWork_fieldTable, g_beNDMWMdlPlayerInfoWork_fieldHandles, g_beNDMWMdlPlayerInfoWork_fieldOffsets, base);
}

static const char *g_beNDMWMdlPlayerInfoWork_damageSeqNames[] = {
    "SQ_SDMG",
    "SQ_MDMG",
    "SQ_LDMG",
    "SQ_DDMG",
    "SQ_DEAD",
    "SQ_SDMGC",
    "SQ_SDMGF",
    "SQ_SDMGI",
    "SQ_SDMGT",
    "SQ_SDMGD",
};
static int g_beNDMWMdlPlayerInfoWork_damageSeqValues[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
};

igMetaEnum *DamageSeq_GetMetaEnum(void) {
    if (g_beNDMWMdlPlayerInfoWork_damageSeqMetaEnum == 0) {
        g_beNDMWMdlPlayerInfoWork_damageSeqMetaEnum = igMetaEnum_Create("DamageSeq", g_beNDMWMdlPlayerInfoWork_damageSeqNames, g_beNDMWMdlPlayerInfoWork_damageSeqValues, 10);
    }
    return g_beNDMWMdlPlayerInfoWork_damageSeqMetaEnum;
}

static const char *g_beNDMWMdlPlayerInfoWork_statusNameNames[] = {
    "POISON",
    "ATTACKDOWN",
    "POWERDOWN",
    "BIND",
    "REFRACT",
    "SPEEDUP",
    "POWERUP",
    "METAL",
    "SLEEP",
    "STUN",
    "RARE",
};
static int g_beNDMWMdlPlayerInfoWork_statusNameValues[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    0xa,
};

igMetaEnum *StatusName_GetMetaEnum(void) {
    if (g_beNDMWMdlPlayerInfoWork_statusNameMetaEnum == 0) {
        g_beNDMWMdlPlayerInfoWork_statusNameMetaEnum = igMetaEnum_Create("StatusName", g_beNDMWMdlPlayerInfoWork_statusNameNames, g_beNDMWMdlPlayerInfoWork_statusNameValues, 11);
    }
    return g_beNDMWMdlPlayerInfoWork_statusNameMetaEnum;
}

static const char *g_beNDMWMdlPlayerInfoWork_msgActionNames[] = {
    "SETPOISON",
    "SETSLEEP",
    "SETSTUN",
    "SETBIND",
    "SETATTACKDOWN",
    "SETPOWERDOWN",
    "SETRAREICON",
    "SETSPEEDUP",
    "SETPOWERUP",
    "SETREFRACT",
    "SETMETAL",
    "CLEARMETAL",
    "CHECKSTATUS",
    "CLEARSTATUS",
    "ALLCLEARSTATUS",
    "GETPEBASEWORK",
};
static int g_beNDMWMdlPlayerInfoWork_msgActionValues[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    0xa,
    0xb,
    0xc,
    0xd,
    0xe,
    0xf,
};

igMetaEnum *MsgAction_GetMetaEnum(void) {
    if (g_beNDMWMdlPlayerInfoWork_msgActionMetaEnum == 0) {
        g_beNDMWMdlPlayerInfoWork_msgActionMetaEnum = igMetaEnum_Create("MsgAction", g_beNDMWMdlPlayerInfoWork_msgActionNames, g_beNDMWMdlPlayerInfoWork_msgActionValues, 16);
    }
    return g_beNDMWMdlPlayerInfoWork_msgActionMetaEnum;
}

