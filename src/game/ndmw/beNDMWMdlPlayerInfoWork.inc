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

void beNDMWMdlPlayerInfoWork_Create(int arg0) {
    FUN_003c0280();
    igMetaObject_CreateInstance(g_beNDMWMdlPlayerInfoWork_metaObject, arg0);
}

igMetaObject *FUN_003bfcc0(void) {
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
    FUN_003c0280();
done:
    return g_beNDMWMdlPlayerInfoWork_metaObject;
}

int beNDMWMdlPlayerInfoWork_GetVTable(void) {
    PlayerInfoWorkView work;
    return *(int *)((char *)&work + *(int *)((char *)g_objectSystem[0] + 916));
}

Obj_3bfde0 *FUN_003bfde0(Obj_3bfde0 *arg0, short arg1) {
    if (arg0) {
        arg0->vt = g_beNDMWMdlPEBaseInfoWork_vtable;
        arg0->rel(&arg0->m268);
        arg0->rel(&arg0->m264);
        arg0->rel(&arg0->m252);
        arg0->rel(&arg0->m248);
        arg0->rel(&arg0->m244);
        arg0->rel(&arg0->m240);
        if (arg0) {
            arg0->vt = g_beModelCtrlInfoWork_vtable;
            FUN_00198190((char *)arg0 + 232, -1);
            FUN_00350e90((char *)arg0 + 228, -1);
            igStringRef_Destruct((char *)arg0 + 220, -1);
            FUN_00350e10((char *)arg0 + 212, -1);
            FUN_00229350((char *)arg0 + 208, -1);
            FUN_00350d90((char *)arg0 + 204, -1);
            FUN_00350d10((char *)arg0 + 200, -1);
            igStringRef_Destruct((char *)arg0 + 184, -1);
            igStringRef_Destruct((char *)arg0 + 180, -1);
            FUN_00350c90((char *)arg0 + 176, -1);
            FUN_0034c1b0((char *)arg0 + 172, -1);
            igStringRef_Destruct((char *)arg0 + 116, -1);
            igStringRef_Destruct((char *)arg0 + 96, -1);
            igStringRef_Destruct((char *)arg0 + 92, -1);
            igStringRef_Destruct((char *)arg0 + 88, -1);
            FUN_00350c10((char *)arg0 + 80, -1);
            igStringRef_Destruct((char *)arg0 + 76, -1);
            FUN_001354b0((char *)arg0 + 72, -1);
            igStringRef_Destruct((char *)arg0 + 56, -1);
            igStringRef_Destruct((char *)arg0 + 52, -1);
            igStringRef_Destruct((char *)arg0 + 48, -1);
            igSmartPointer_igIntList_Destruct((char *)arg0 + 44, -1);
            igSmartPointer_igStringRefList_Destruct((char *)arg0 + 40, -1);
            igSmartPointer_igStringRefList_Destruct((char *)arg0 + 36, -1);
            FUN_00350b90((char *)arg0 + 24, -1);
            igStringRef_Destruct((char *)arg0 + 20, -1);
            FUN_00350b10((char *)arg0 + 12, -1);
            FUN_00350b10((char *)arg0 + 8, -1);
        }
        if (arg1 > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

void FUN_003c0280(void)
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

igMetaObject *FUN_003c0340(void) {
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
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWMdlPlayerInfoWork_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWMdlPlayerInfoWork_ctorTable, 8);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beNDMWMdlPlayerInfoWork_fieldTable, g_beNDMWMdlPlayerInfoWork_fieldHandles, g_beNDMWMdlPlayerInfoWork_fieldOffsets, temp_s2);
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

