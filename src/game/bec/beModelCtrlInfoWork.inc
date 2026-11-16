igMetaObject *g_beModelCtrlInfoWork_metaObject;
igMetaField *g_beModelCtrlInfoWork_mHpMetaField;
igMetaField *g_beModelCtrlInfoWork_hpMetaField;
igMetaField *g_beModelCtrlInfoWork_recNoMetaField;
igMetaField *g_beModelCtrlInfoWork_seqCodeNameMetaField;
igMetaField *g_beModelCtrlInfoWork_comDataMetaField;
igMetaField *g_beModelCtrlInfoWork_comIndexMetaField;
igMetaField *g_beModelCtrlInfoWork_comLabelCountMetaField;
igMetaField *g_beModelCtrlInfoWork_labelSeqListMetaField;
igMetaField *g_beModelCtrlInfoWork_labelNameListMetaField;
igMetaField *g_beModelCtrlInfoWork_labelOffsetListMetaField;
igMetaField *g_beModelCtrlInfoWork_luaBHitMetaField;
igMetaField *g_beModelCtrlInfoWork_luaWHitMetaField;
igMetaField *g_beModelCtrlInfoWork_luaFHitMetaField;
igMetaField *g_beModelCtrlInfoWork_ctrlSt0MetaField;
igMetaField *g_beModelCtrlInfoWork_ctrlSt1MetaField;
igMetaField *g_beModelCtrlInfoWork_isOnCtrlMetaField;
igMetaField *g_beModelCtrlInfoWork_isOnFreezeMetaField;
igMetaField *g_beModelCtrlInfoWork_pdMoveDataListMetaField;
igMetaField *g_beModelCtrlInfoWork_wCheckNameMetaField;
igMetaField *g_beModelCtrlInfoWork_aIMetaField;
igMetaField *g_beModelCtrlInfoWork_aIHOffsetYMetaField;
igMetaField *g_beModelCtrlInfoWork_targetModeMetaField;
igMetaField *g_beModelCtrlInfoWork_targetKindMetaField;
igMetaField *g_beModelCtrlInfoWork_targetSpc1MetaField;
igMetaField *g_beModelCtrlInfoWork_targetPosMetaField;
igMetaField *g_beModelCtrlInfoWork_keyInputMetaField;
igMetaField *g_beModelCtrlInfoWork_keyEventNameMetaField;
igMetaField *g_beModelCtrlInfoWork_isHitCheckMetaField;
igMetaField *g_beModelCtrlInfoWork_mutekiCountMetaField;
igMetaField *g_beModelCtrlInfoWork_targetDirectionMetaField;
igMetaField *g_beModelCtrlInfoWork_directionLimiterMetaField;
igMetaField *g_beModelCtrlInfoWork_directionMetaField;
igMetaField *g_beModelCtrlInfoWork_svLODHighRangeMetaField;
igMetaField *g_beModelCtrlInfoWork_isPosLockMetaField;
igMetaField *g_beModelCtrlInfoWork_posLockNodeMetaField;
igMetaField *g_beModelCtrlInfoWork_posLockTrcMetaField;
igMetaField *g_beModelCtrlInfoWork_posLockModelNameMetaField;
igMetaField *g_beModelCtrlInfoWork_posLockBoneNameMetaField;
igMetaField *g_beModelCtrlInfoWork_posLockOffsetMetaField;
igMetaField *g_beModelCtrlInfoWork_moveObjectListMetaField;
igMetaField *g_beModelCtrlInfoWork_rideOnDataMetaField;
igMetaField *g_beModelCtrlInfoWork_debugHitBoxNodeMetaField;
igMetaField *g_beModelCtrlInfoWork_hitBodyMetaField;
igMetaField *g_beModelCtrlInfoWork_isWallCheckMetaField;
igMetaField *g_beModelCtrlInfoWork_isFloorCheckMetaField;
igMetaField *g_beModelCtrlInfoWork_isFallCheckMetaField;
igMetaField *g_beModelCtrlInfoWork_hitParentNameMetaField;
igMetaField *g_beModelCtrlInfoWork_hitParentRamNoMetaField;
igMetaField *g_beModelCtrlInfoWork_subCommandMetaField;
igMetaField *g_beModelCtrlInfoWork_baseAABoxMetaField;

void beModelCtrlInfoWork_Create(int allocator) {
    beModelCtrlInfoWork_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588888, allocator);
}

igMetaObject *beModelCtrlInfoWork_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlInfoWork_metaObject == 0) {
        g_beModelCtrlInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beModelCtrlInfoWork_metaObject;
}

void *beModelCtrlInfoWork_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlInfoWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlInfoWork_EnsureRegistered();
    }
    return g_beModelCtrlInfoWork_metaObject;
}

int beModelCtrlInfoWork_GetVTable(void) {
    ModelCtrlInfoWorkView work;
    return *(int *)((char *)&work + *(int *)((char *)g_objectSystem[0] + 916));
}

void *beModelCtrlInfoWork_Destroy(beNDMWMdlPlayer2InfoWork *arg0, long long arg1) {
    void *p;
    igObject *o;
    int *h;
    int rc;

    if (arg0 != 0) {
        arg0->_vtable = (int)&g_beModelCtrlInfoWork_vtable[0];
        OBJ(arg0->_baseAABox)
        OBJ(arg0->_subCommand)
        STR(arg0->_hitParentName)
        OBJ(arg0->_hitBody)
        OBJ(arg0->_debugHitBoxNode)
        OBJ(arg0->_rideOnData)
        OBJ(arg0->_moveObjectList)
        STR(arg0->_posLockBoneName)
        STR(arg0->_posLockModelName)
        OBJ(arg0->_posLockTrc)
        OBJ(arg0->_posLockNode)
        STR(arg0->_keyEventName)
        STR(arg0->_targetSpc1)
        STR(arg0->_targetKind)
        STR(arg0->_targetMode)
        OBJ(arg0->_aI)
        STR(arg0->_wCheckName)
        OBJ(arg0->_pdMoveDataList)
        STR(arg0->_luaFHit)
        STR(arg0->_luaWHit)
        STR(arg0->_luaBHit)
        OBJ(arg0->_labelOffsetList)
        OBJ(arg0->_labelNameList)
        OBJ(arg0->_labelSeqList)
        OBJ(arg0->_comData)
        STR(arg0->_seqCodeName)
        OBJ(arg0->_hp)
        OBJ(arg0->_mHp)
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            Memory_FreeBufferAliasC(arg0);
        }
    }
    return arg0;
}

igSmartPointer<igObject> *igSmartPointer_beDataObjInt_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlData_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoAI_Destruct(igSmartPointer<igObject> *self, long long delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoDataTrc_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlMoveObjectList_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoRideOn_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoHitBody_Destruct(igSmartPointer<igObject> *self, int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if ((short)delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlSubCom_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((void *)object);
        }
        if (delete_storage > 0) __dl__FPv(self);
    }
    return self;
}

int *igSmartPointer_beModelCtrlSubCom_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_beModelCtrlInfoHitBody_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_igGroup_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_beModelCtrlInfoRideOn_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_beModelCtrlMoveObjectList_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_beModelCtrlInfoDataTrc_Construct(int *p)
{
    *p = 0;
    return p;
}

int *igSmartPointer_beModelCtrlNode2_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_beModelCtrlInfoAI_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_beModelCtrlData_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

int *igSmartPointer_beDataObjInt_Construct(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void beModelCtrlInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoWork_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoWork_callbackList[] = { beDataObjInt_EnsureRegistered, beModelCtrlData_EnsureRegistered, igStringRefList_EnsureRegistered, igIntList_EnsureRegistered, igFloatList_EnsureRegistered, beModelCtrlInfoAI_EnsureRegistered, beModelCtrlNode2_EnsureRegistered, beModelCtrlInfoDataTrc_EnsureRegistered, beModelCtrlMoveObjectList_EnsureRegistered, beModelCtrlInfoRideOn_EnsureRegistered, igGroup_EnsureRegistered, beModelCtrlInfoHitBody_EnsureRegistered, beModelCtrlSubCom_EnsureRegistered, igAABox_EnsureRegistered, 0 };

void *beModelCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoWork_GetMetaObjectFunction,
        "beModelCtrlInfoWork",
        0xec, /* instance size */
        beModelCtrlInfoWork_GetVTable,
        beModelCtrlInfoWork_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoWork_callbackList /* callback list */
    );
}

void beModelCtrlInfoWork_GetMetaObjectFunction(void)
{
    beModelCtrlInfoWork_GetMetaObject();
}

static FieldFactory g_beModelCtrlInfoWork_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igObjectRefMetaField_Create,
    igFloatMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igVec3fMetaField_CreateInstance,
    igBoolMetaField_Create,
    igStringMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igVec3fMetaField_CreateInstance,
    igVec3fMetaField_CreateInstance,
    igVec3fMetaField_CreateInstance,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igVec3fMetaField_CreateInstance,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igStringMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beModelCtrlInfoWork_fieldTable[] = {
    "_mHp",
    "_hp",
    "_recNo",
    "_seqCodeName",
    "_comData",
    "_comIndex",
    "_comLabelCount",
    "_labelSeqList",
    "_labelNameList",
    "_labelOffsetList",
    "_luaBHit",
    "_luaWHit",
    "_luaFHit",
    "_ctrlSt0",
    "_ctrlSt1",
    "_isOnCtrl",
    "_isOnFreeze",
    "_pdMoveDataList",
    "_wCheckName",
    "_aI",
    "_aIHOffsetY",
    "_targetMode",
    "_targetKind",
    "_targetSpc1",
    "_targetPos",
    "_keyInput",
    "_keyEventName",
    "_isHitCheck",
    "_mutekiCount",
    "_targetDirection",
    "_directionLimiter",
    "_direction",
    "_svLODHighRange",
    "_isPosLock",
    "_posLockNode",
    "_posLockTrc",
    "_posLockModelName",
    "_posLockBoneName",
    "_posLockOffset",
    "_moveObjectList",
    "_rideOnData",
    "_debugHitBoxNode",
    "_hitBody",
    "_isWallCheck",
    "_isFloorCheck",
    "_isFallCheck",
    "_hitParentName",
    "_hitParentRamNo",
    "_subCommand",
    "_baseAABox",
};
static igMetaField **g_beModelCtrlInfoWork_fieldHandles[] = {
    &g_beModelCtrlInfoWork_mHpMetaField,
    &g_beModelCtrlInfoWork_hpMetaField,
    &g_beModelCtrlInfoWork_recNoMetaField,
    &g_beModelCtrlInfoWork_seqCodeNameMetaField,
    &g_beModelCtrlInfoWork_comDataMetaField,
    &g_beModelCtrlInfoWork_comIndexMetaField,
    &g_beModelCtrlInfoWork_comLabelCountMetaField,
    &g_beModelCtrlInfoWork_labelSeqListMetaField,
    &g_beModelCtrlInfoWork_labelNameListMetaField,
    &g_beModelCtrlInfoWork_labelOffsetListMetaField,
    &g_beModelCtrlInfoWork_luaBHitMetaField,
    &g_beModelCtrlInfoWork_luaWHitMetaField,
    &g_beModelCtrlInfoWork_luaFHitMetaField,
    &g_beModelCtrlInfoWork_ctrlSt0MetaField,
    &g_beModelCtrlInfoWork_ctrlSt1MetaField,
    &g_beModelCtrlInfoWork_isOnCtrlMetaField,
    &g_beModelCtrlInfoWork_isOnFreezeMetaField,
    &g_beModelCtrlInfoWork_pdMoveDataListMetaField,
    &g_beModelCtrlInfoWork_wCheckNameMetaField,
    &g_beModelCtrlInfoWork_aIMetaField,
    &g_beModelCtrlInfoWork_aIHOffsetYMetaField,
    &g_beModelCtrlInfoWork_targetModeMetaField,
    &g_beModelCtrlInfoWork_targetKindMetaField,
    &g_beModelCtrlInfoWork_targetSpc1MetaField,
    &g_beModelCtrlInfoWork_targetPosMetaField,
    &g_beModelCtrlInfoWork_keyInputMetaField,
    &g_beModelCtrlInfoWork_keyEventNameMetaField,
    &g_beModelCtrlInfoWork_isHitCheckMetaField,
    &g_beModelCtrlInfoWork_mutekiCountMetaField,
    &g_beModelCtrlInfoWork_targetDirectionMetaField,
    &g_beModelCtrlInfoWork_directionLimiterMetaField,
    &g_beModelCtrlInfoWork_directionMetaField,
    &g_beModelCtrlInfoWork_svLODHighRangeMetaField,
    &g_beModelCtrlInfoWork_isPosLockMetaField,
    &g_beModelCtrlInfoWork_posLockNodeMetaField,
    &g_beModelCtrlInfoWork_posLockTrcMetaField,
    &g_beModelCtrlInfoWork_posLockModelNameMetaField,
    &g_beModelCtrlInfoWork_posLockBoneNameMetaField,
    &g_beModelCtrlInfoWork_posLockOffsetMetaField,
    &g_beModelCtrlInfoWork_moveObjectListMetaField,
    &g_beModelCtrlInfoWork_rideOnDataMetaField,
    &g_beModelCtrlInfoWork_debugHitBoxNodeMetaField,
    &g_beModelCtrlInfoWork_hitBodyMetaField,
    &g_beModelCtrlInfoWork_isWallCheckMetaField,
    &g_beModelCtrlInfoWork_isFloorCheckMetaField,
    &g_beModelCtrlInfoWork_isFallCheckMetaField,
    &g_beModelCtrlInfoWork_hitParentNameMetaField,
    &g_beModelCtrlInfoWork_hitParentRamNoMetaField,
    &g_beModelCtrlInfoWork_subCommandMetaField,
    &g_beModelCtrlInfoWork_baseAABoxMetaField,
};
static int g_beModelCtrlInfoWork_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
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
    69,
    72,
    76,
    80,
    84,
    88,
    92,
    96,
    100,
    112,
    116,
    120,
    124,
    128,
    140,
    152,
    164,
    168,
    172,
    176,
    180,
    184,
    188,
    200,
    204,
    208,
    212,
    216,
    217,
    218,
    220,
    224,
    228,
    232,
};

void beModelCtrlInfoWork_InitFields(void) {
    void *mHp;
    void *posLockTrc;
    void *moveObjectList;
    void *rideOnData;
    void *debugHitBoxNode;
    void *hitBody;
    void *subCommand;
    void *baseAABox;
    void *hp;
    void *comData;
    void *labelSeqList;
    void *labelNameList;
    void *labelOffsetList;
    void *pdMoveDataList;
    void *aI;
    void *posLockNode;
    int base;
    void *meta;

    meta = (void *)g_beModelCtrlInfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoWork_ctorTable, 0x32);
    mHp = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)mHp)->_metaObject = (int)beDataObjInt_GetOrCreateMetaObject();
    ((igRefMetaField *)mHp)->_construct = 1;
    hp = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)hp)->_metaObject = (int)beDataObjInt_GetOrCreateMetaObject();
    ((igRefMetaField *)hp)->_construct = 1;
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 2), -1);
    comData = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)comData)->_metaObject = (int)beModelCtrlData_GetOrCreateMetaObject();
    labelSeqList = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)labelSeqList)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    labelNameList = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)labelNameList)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    labelOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)labelOffsetList)->_metaObject = igIntList_GetOrCreateMetaObject();
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 0xA), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 0xB), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 0xC), 0);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 0xF), 1);
    pdMoveDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 0x11));
    ((igObjectRefMetaField *)pdMoveDataList)->_metaObject = igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)pdMoveDataList)->_construct = 1;
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 0x12), 0);
    aI = (void *)(igMetaObject_GetFieldAt(meta, base + 0x13));
    ((igObjectRefMetaField *)aI)->_metaObject = (int)beModelCtrlInfoAI_GetOrCreateMetaObject();
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 0x15), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 0x16), 0);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 0x17), 0);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 0x1C), 0.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 0x20), -1.0f);
    posLockNode = (void *)(igMetaObject_GetFieldAt(meta, base + 0x22));
    ((igObjectRefMetaField *)posLockNode)->_metaObject = (int)beModelCtrlNode2_GetOrCreateMetaObject();
    posLockTrc = (void *)(igMetaObject_GetFieldAt(meta, base + 0x23));
    ((igObjectRefMetaField *)posLockTrc)->_metaObject = (int)beModelCtrlInfoDataTrc_GetOrCreateMetaObject();
    moveObjectList = (void *)(igMetaObject_GetFieldAt(meta, base + 0x27));
    ((igObjectRefMetaField *)moveObjectList)->_metaObject = (int)beModelCtrlMoveObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)moveObjectList)->_construct = 1;
    rideOnData = (void *)(igMetaObject_GetFieldAt(meta, base + 0x28));
    ((igObjectRefMetaField *)rideOnData)->_metaObject = (int)beModelCtrlInfoRideOn_GetOrCreateMetaObject();
    debugHitBoxNode = (void *)(igMetaObject_GetFieldAt(meta, base + 0x29));
    ((igObjectRefMetaField *)debugHitBoxNode)->_metaObject = igGroup_GetOrCreateMetaObject();
    hitBody = (void *)(igMetaObject_GetFieldAt(meta, base + 0x2A));
    ((igObjectRefMetaField *)hitBody)->_metaObject = (int)beModelCtrlInfoHitBody_GetOrCreateMetaObject();
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 0x2B), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 0x2C), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 0x2D), 1);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 0x2E), 0);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 0x2F), 0);
    subCommand = (void *)(igMetaObject_GetFieldAt(meta, base + 0x30));
    ((igObjectRefMetaField *)subCommand)->_metaObject = (int)beModelCtrlSubCom_GetOrCreateMetaObject();
    ((igRefMetaField *)subCommand)->_construct = 1;
    baseAABox = (void *)(igMetaObject_GetFieldAt(meta, base + 0x31));
    ((igObjectRefMetaField *)baseAABox)->_metaObject = igAABox_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beModelCtrlInfoWork_fieldTable, g_beModelCtrlInfoWork_fieldHandles, g_beModelCtrlInfoWork_fieldOffsets, base);
}

