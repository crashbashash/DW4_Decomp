igMetaEnum *g_FightCom_metaEnum;
igMetaEnum *g_GameRamMessage_metaEnum;
igMetaObject *g_beNDMWGameRam_metaObject;
igMetaField *g_beNDMWGameRam_dBShinkaMetaField;
igMetaField *g_beNDMWGameRam_dBPcTechMetaField;
igMetaField *g_beNDMWGameRam_dBWeaponMetaField;
igMetaField *g_beNDMWGameRam_dBArmor1MetaField;
igMetaField *g_beNDMWGameRam_dBArmor2MetaField;
igMetaField *g_beNDMWGameRam_dBAbChipMetaField;
igMetaField *g_beNDMWGameRam_dBEnemyMetaField;
igMetaField *g_beNDMWGameRam_dBEneatkMetaField;
igMetaField *g_beNDMWGameRam_commonDataListMetaField;
igMetaField *g_beNDMWGameRam_playerDataListListMetaField;
igMetaField *g_beNDMWGameRam_isDispFightDataMetaField;

static const char *g_FightCom_commandNames[] = {
    "E2PISHITCHECK",
    "P2EISHITCHECK",
    "P2EISCRITICAL",
    "E2PDAMAGE",
    "E2PDAMAGERANK",
    "P2EDAMAGE",
    "P2EEXPUP",
    "E2PSTUNTIME",
    "E2PPOISONTIME",
    "E2PSLEEPTIME",
    "E2PBINDTIME",
    "E2PATKDWNTIME",
    "E2PPOWDWNTIME",
    "P2ESKILLUP",
    "P2ESTUNTIME",
    "P2EPOISONTIME",
    "P2ESLEEPTIME",
    "P2EBINDTIME",
    "P2EATKDWNTIME",
    "P2EPOWDWNTIME",
    "P2PKOUKAMAGIC",
    "GETPATKZOKUSEI",
};
static int g_FightCom_commandIds[] = {
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
    0x10,
    0x11,
    0x12,
    0x13,
    0x14,
    0x15,
};

igMetaEnum *FightCom_GetMetaEnum(void) {
    if (g_FightCom_metaEnum == 0) {
        g_FightCom_metaEnum = igMetaEnum_Create("FightCom", g_FightCom_commandNames, g_FightCom_commandIds, 22);
    }
    return g_FightCom_metaEnum;
}

static const char *g_GameRamMessage_commandNames[] = {
    "GETCOMMON",
    "GETPLAYER",
    "GETPLAYER1",
    "GETPLAYER2",
    "GETPLAYER3",
    "GETPLAYER4",
    "GAMEDATAINIT",
    "GAMESTART",
    "GAMEREMOVE",
    "ADDHP",
    "ADDMP",
    "RECALCPLAYER",
    "BASE2CURRENT",
    "CURRENT2BASE",
    "WEAPONEQUIPCHECK",
    "WEAPONEQUIPSTRONG",
    "DEADRESTART",
    "CTRLITEM",
    "FIGHTCALC",
    "DISPFIGHTDATA",
    "BKCHIPBITEXP",
    "CTRLPLAYER",
};
static int g_GameRamMessage_commandIds[] = {
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
    0x10,
    0x11,
    0x12,
    0x13,
    0x14,
    0x15,
};

igMetaEnum *GameRamMessage_GetMetaEnum(void) {
    if (g_GameRamMessage_metaEnum == 0) {
        g_GameRamMessage_metaEnum = igMetaEnum_Create("Message", g_GameRamMessage_commandNames, g_GameRamMessage_commandIds, 22);
    }
    return g_GameRamMessage_metaEnum;
}

void beNDMWGameRam_CreateInstance(int arg0) {
    FUN_003c9f70();
    igMetaObject_CreateInstance(g_beNDMWGameRam_metaObject, arg0);
}

igMetaObject *FUN_003c9ce0(void) {
    if (g_beNDMWGameRam_metaObject == 0) {
        g_beNDMWGameRam_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWGameRam_metaObject;
}

igMetaObject *beNDMWGameRam_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWGameRam_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_003c9f70();
done:
    return g_beNDMWGameRam_metaObject;
}

int beNDMWGameRam_GetVTable(void) {
    struct Obj_3c9d80 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053ea40[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053ea40[0];
    FUN_003c9ef0((void **)&obj.w17, (short)(-1));
    FUN_003ba350((void **)&obj.w16, (short)(-1));
    FUN_00365e90(&obj.w15, -1);
    FUN_00365e90(&obj.w14, -1);
    FUN_00365e90(&obj.w13, -1);
    FUN_00365e90(&obj.w12, -1);
    FUN_00365e90(&obj.w11, -1);
    FUN_00365e90(&obj.w10, -1);
    FUN_00365e90(&obj.w9, -1);
    FUN_00365e90(&obj.w8, -1);
    FUN_0033f5e0(&obj, 0);
    return t;
}

void **FUN_003c9ef0(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy(r);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void FUN_003c9f70(void)
{
    igMetaObject_RunStaticInit(beNDMWGameRam_Register);
}

static igMetaObjectCallback g_beNDMWGameRam_callbackList[] = { FUN_00365b00, FUN_00364170, FUN_00363fa0, 0 };

void *beNDMWGameRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWGameRam_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWGameRam_GetMetaObject,
        "beNDMWGameRam",
        0x4c, /* instance size */
        beNDMWGameRam_GetVTable,
        beNDMWGameRam_InitFields,
        0, /* extra callback item */
        g_beNDMWGameRam_callbackList /* callback list */
    );
}

void beNDMWGameRam_GetMetaObject(void)
{
    beNDMWGameRam_ResolveMetaObject();
}

static FieldFactory g_beNDMWGameRam_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beNDMWGameRam_fieldTable[] = {
    "_dBShinka",
    "_dBPcTech",
    "_dBWeapon",
    "_dBArmor1",
    "_dBArmor2",
    "_dBAbChip",
    "_dBEnemy",
    "_dBEneatk",
    "_commonDataList",
    "_playerDataListList",
    "_isDispFightData",
};
static igMetaField **g_beNDMWGameRam_fieldHandles[] = {
    &g_beNDMWGameRam_dBShinkaMetaField,
    &g_beNDMWGameRam_dBPcTechMetaField,
    &g_beNDMWGameRam_dBWeaponMetaField,
    &g_beNDMWGameRam_dBArmor1MetaField,
    &g_beNDMWGameRam_dBArmor2MetaField,
    &g_beNDMWGameRam_dBAbChipMetaField,
    &g_beNDMWGameRam_dBEnemyMetaField,
    &g_beNDMWGameRam_dBEneatkMetaField,
    &g_beNDMWGameRam_commonDataListMetaField,
    &g_beNDMWGameRam_playerDataListListMetaField,
    &g_beNDMWGameRam_isDispFightDataMetaField,
};
static int g_beNDMWGameRam_fieldOffsets[] = {
    32,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
};

void beNDMWGameRam_InitFields(void) {
    void *temp_s2;
    void *temp_s2_10;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s2_8;
    void *temp_s2_9;
    void *temp_s1;
    int temp_s0;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    temp_s1 = (void *)g_beNDMWGameRam_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_beNDMWGameRam_ctorTable, 0xB);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_003658e0();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_003658e0();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_003658e0();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_003658e0();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_003658e0();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_003658e0();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_003658e0();
    temp_s2_8 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_8)->_metaObject = FUN_003658e0();
    temp_s2_9 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_9)->_metaObject = FUN_00364090();
    temp_s2_10 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_10)->_metaObject = FUN_00363ec0();
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_beNDMWGameRam_fieldTable, g_beNDMWGameRam_fieldHandles, g_beNDMWGameRam_fieldOffsets, temp_s0);
}

