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

beModelCtrlInfoWork *beModelCtrlInfoWork_Create(int allocator) {
    beModelCtrlInfoWork_EnsureRegistered();
    return (beModelCtrlInfoWork *)igMetaObject_CreateInstance(g_beModelCtrlInfoWork_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beModelCtrlInfoWork_GetOrCreateMetaObject(void) {
    if (g_beModelCtrlInfoWork_metaObject == 0) {
        g_beModelCtrlInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
    return *(int *)((char *)&work + g_objectSystem->vtableProbeOffset);
}

void *beModelCtrlInfoWork_Destroy(beModelCtrlInfoWork *self, long long delete_storage) {
    if (self != 0) {
        self->_vtable = (int)&g_beModelCtrlInfoWork_vtable[0];
        igObjectRef_Release((igObject **)&self->_baseAABox);
        igObjectRef_Release((igObject **)&self->_subCommand);
        igStringRef_Release((char **)&self->_hitParentName);
        igObjectRef_Release((igObject **)&self->_hitBody);
        igObjectRef_Release((igObject **)&self->_debugHitBoxNode);
        igObjectRef_Release((igObject **)&self->_rideOnData);
        igObjectRef_Release((igObject **)&self->_moveObjectList);
        igStringRef_Release((char **)&self->_posLockBoneName);
        igStringRef_Release((char **)&self->_posLockModelName);
        igObjectRef_Release((igObject **)&self->_posLockTrc);
        igObjectRef_Release((igObject **)&self->_posLockNode);
        igStringRef_Release((char **)&self->_keyEventName);
        igStringRef_Release((char **)&self->_targetSpc1);
        igStringRef_Release((char **)&self->_targetKind);
        igStringRef_Release((char **)&self->_targetMode);
        igObjectRef_Release((igObject **)&self->_aI);
        igStringRef_Release((char **)&self->_wCheckName);
        igObjectRef_Release((igObject **)&self->_pdMoveDataList);
        igStringRef_Release((char **)&self->_luaFHit);
        igStringRef_Release((char **)&self->_luaWHit);
        igStringRef_Release((char **)&self->_luaBHit);
        igObjectRef_Release((igObject **)&self->_labelOffsetList);
        igObjectRef_Release((igObject **)&self->_labelNameList);
        igObjectRef_Release((igObject **)&self->_labelSeqList);
        igObjectRef_Release((igObject **)&self->_comData);
        igStringRef_Release((char **)&self->_seqCodeName);
        igObjectRef_Release((igObject **)&self->_hp);
        igObjectRef_Release((igObject **)&self->_mHp);
        if ((short)delete_storage > 0) {
            Memory_FreeBufferAliasC(self);
        }
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beDataObjInt_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlData_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoAI_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoDataTrc_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlMoveObjectList_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoRideOn_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoHitBody_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlSubCom_Destruct(igSmartPointer<igObject> *self, short delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if (delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlSubCom_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoHitBody_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igGroup_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoRideOn_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlMoveObjectList_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoDataTrc_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlNode2_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlInfoAI_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beModelCtrlData_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beDataObjInt_Construct(igSmartPointer<igObject> *self)
{
    self->p = 0;
    return self;
}

void beModelCtrlInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlInfoWork_Register);
}

static igMetaObjectCallback g_beModelCtrlInfoWork_callbackList[] = { beDataObjInt_EnsureRegistered, beModelCtrlData_EnsureRegistered, igStringRefList_EnsureRegistered, igIntList_EnsureRegistered, igFloatList_EnsureRegistered, beModelCtrlInfoAI_EnsureRegistered, beModelCtrlNode2_EnsureRegistered, beModelCtrlInfoDataTrc_EnsureRegistered, beModelCtrlMoveObjectList_EnsureRegistered, beModelCtrlInfoRideOn_EnsureRegistered, igGroup_EnsureRegistered, beModelCtrlInfoHitBody_EnsureRegistered, beModelCtrlSubCom_EnsureRegistered, igAABox_EnsureRegistered, 0 };

CallbackArray *beModelCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlInfoWork_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
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
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    igBoolMetaField_Create,
    igStringMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
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
    igMetaObject *meta;

    meta = g_beModelCtrlInfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlInfoWork_ctorTable, 0x32);
    mHp = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)mHp)->_metaObject = (int)beDataObjInt_GetOrCreateMetaObject();
    ((igRefMetaField *)mHp)->_construct = 1;
    hp = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)hp)->_metaObject = (int)beDataObjInt_GetOrCreateMetaObject();
    ((igRefMetaField *)hp)->_construct = 1;
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 2)))->setDefault(-1);
    comData = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)comData)->_metaObject = (int)beModelCtrlData_GetOrCreateMetaObject();
    labelSeqList = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)labelSeqList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    labelNameList = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)labelNameList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    labelOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)labelOffsetList)->_metaObject = (int)igIntList_GetOrCreateMetaObject();
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, base + 0xA)))->setDefault(0);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, base + 0xB)))->setDefault(0);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, base + 0xC)))->setDefault(0);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 0xF)))->setDefault(1);
    pdMoveDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 0x11));
    ((igObjectRefMetaField *)pdMoveDataList)->_metaObject = (int)igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)pdMoveDataList)->_construct = 1;
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x12)))->setDefault(0);
    aI = (void *)(igMetaObject_GetFieldAt(meta, base + 0x13));
    ((igObjectRefMetaField *)aI)->_metaObject = (int)beModelCtrlInfoAI_GetOrCreateMetaObject();
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x15)))->setDefault(0);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x16)))->setDefault(0);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x17)))->setDefault(0);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x1C)))->setDefault(0.0f);
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x20)))->setDefault(-1.0f);
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
    ((igObjectRefMetaField *)debugHitBoxNode)->_metaObject = (int)igGroup_GetOrCreateMetaObject();
    hitBody = (void *)(igMetaObject_GetFieldAt(meta, base + 0x2A));
    ((igObjectRefMetaField *)hitBody)->_metaObject = (int)beModelCtrlInfoHitBody_GetOrCreateMetaObject();
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x2B)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x2C)))->setDefault(1);
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x2D)))->setDefault(1);
    ((Gap::Core::igStringMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x2E)))->setDefault(0);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 0x2F)))->setDefault(0);
    subCommand = (void *)(igMetaObject_GetFieldAt(meta, base + 0x30));
    ((igObjectRefMetaField *)subCommand)->_metaObject = (int)beModelCtrlSubCom_GetOrCreateMetaObject();
    ((igRefMetaField *)subCommand)->_construct = 1;
    baseAABox = (void *)(igMetaObject_GetFieldAt(meta, base + 0x31));
    ((igObjectRefMetaField *)baseAABox)->_metaObject = (int)igAABox_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beModelCtrlInfoWork_fieldTable, g_beModelCtrlInfoWork_fieldHandles, g_beModelCtrlInfoWork_fieldOffsets, base);
}

