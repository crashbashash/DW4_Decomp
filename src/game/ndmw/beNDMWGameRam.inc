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

beNDMWGameRam *beNDMWGameRam_CreateInstance(int allocator) {
    beNDMWGameRam_EnsureRegistered();
    return (beNDMWGameRam *)igMetaObject_CreateInstance(g_beNDMWGameRam_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWGameRam_GetOrCreateMetaObject(void) {
    if (g_beNDMWGameRam_metaObject == 0) {
        g_beNDMWGameRam_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWGameRam_metaObject;
}

igMetaObject *beNDMWGameRam_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWGameRam_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beNDMWGameRam_EnsureRegistered();
done:
    return g_beNDMWGameRam_metaObject;
}

int beNDMWGameRam_GetVTable(void) {
    beNDMWGameRam obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWGameRam_vtable[0];
    obj._dBShinka = 0;
    obj._dBPcTech = 0;
    obj._dBWeapon = 0;
    obj._dBArmor1 = 0;
    obj._dBArmor2 = 0;
    obj._dBAbChip = 0;
    obj._dBEnemy = 0;
    obj._dBEneatk = 0;
    obj._commonDataList = 0;
    obj._playerDataListList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWGameRam_vtable[0];
    igSmartPointer_beDataObjListList_Destruct((igSmartPointer<igObject> *)&obj._playerDataListList, -1);
    beNDMWStatusSubSlot_igSmartPointer_igObject_Destruct((igSmartPointer<igObject> *)&obj._commonDataList, -1);
    igSmartPointer_beDataBase_Destruct((igSmartPointer<igObject> *)&obj._dBEneatk, -1);
    igSmartPointer_beDataBase_Destruct((igSmartPointer<igObject> *)&obj._dBEnemy, -1);
    igSmartPointer_beDataBase_Destruct((igSmartPointer<igObject> *)&obj._dBAbChip, -1);
    igSmartPointer_beDataBase_Destruct((igSmartPointer<igObject> *)&obj._dBArmor2, -1);
    igSmartPointer_beDataBase_Destruct((igSmartPointer<igObject> *)&obj._dBArmor1, -1);
    igSmartPointer_beDataBase_Destruct((igSmartPointer<igObject> *)&obj._dBWeapon, -1);
    igSmartPointer_beDataBase_Destruct((igSmartPointer<igObject> *)&obj._dBPcTech, -1);
    igSmartPointer_beDataBase_Destruct((igSmartPointer<igObject> *)&obj._dBShinka, -1);
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beDataObjListList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beNDMWGameRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWGameRam_Register);
}

static igMetaObjectCallback g_beNDMWGameRam_callbackList[] = { beDataBase_EnsureRegistered, beDataObjList_EnsureRegistered, beDataObjListList_EnsureRegistered, 0 };

CallbackArray *beNDMWGameRam_Register(void) {
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
    void *dBShinka;
    void *playerDataListList;
    void *dBPcTech;
    void *dBWeapon;
    void *dBArmor1;
    void *dBArmor2;
    void *dBAbChip;
    void *dBEnemy;
    void *dBEneatk;
    void *commonDataList;
    void *meta;
    int base;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)g_beNDMWGameRam_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWGameRam_ctorTable, 0xB);
    dBShinka = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)dBShinka)->_metaObject = (int)beDataBase_GetOrCreateMetaObject();
    dBPcTech = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)dBPcTech)->_metaObject = (int)beDataBase_GetOrCreateMetaObject();
    dBWeapon = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2));
    ((igObjectRefMetaField *)dBWeapon)->_metaObject = (int)beDataBase_GetOrCreateMetaObject();
    dBArmor1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)dBArmor1)->_metaObject = (int)beDataBase_GetOrCreateMetaObject();
    dBArmor2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    ((igObjectRefMetaField *)dBArmor2)->_metaObject = (int)beDataBase_GetOrCreateMetaObject();
    dBAbChip = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    ((igObjectRefMetaField *)dBAbChip)->_metaObject = (int)beDataBase_GetOrCreateMetaObject();
    dBEnemy = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6));
    ((igObjectRefMetaField *)dBEnemy)->_metaObject = (int)beDataBase_GetOrCreateMetaObject();
    dBEneatk = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7));
    ((igObjectRefMetaField *)dBEneatk)->_metaObject = (int)beDataBase_GetOrCreateMetaObject();
    commonDataList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8));
    ((igObjectRefMetaField *)commonDataList)->_metaObject = (int)beDataObjList_GetOrCreateMetaObject();
    playerDataListList = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9));
    ((igObjectRefMetaField *)playerDataListList)->_metaObject = (int)beDataObjListList_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWGameRam_fieldTable, g_beNDMWGameRam_fieldHandles, g_beNDMWGameRam_fieldOffsets, base);
}

