igMetaObject *g_beNDMWLoadCtrl2CommonIntf_metaObject;
int g_beNDMWLoadCtrl2CommonIntf_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_messengerMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_systemMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_inforamMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_insightMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_slotSaveDataMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_gameUseDataMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_flagWorkMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_nextStatMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_intfStatMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_mcUtilCtrlMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_kindHardMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_difficultModeMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_isTitleMetaField;
igMetaField *g_beNDMWLoadCtrl2CommonIntf_utilUsePlNoMetaField;

beNDMWLoadCtrl2CommonIntf *beNDMWLoadCtrl2CommonIntf_Create(int allocator) {
    beNDMWLoadCtrl2CommonIntf_EnsureRegistered();
    return (beNDMWLoadCtrl2CommonIntf *)igMetaObject_CreateInstance(g_beNDMWLoadCtrl2CommonIntf_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWLoadCtrl2CommonIntf_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadCtrl2CommonIntf_metaObject == 0) {
        g_beNDMWLoadCtrl2CommonIntf_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWLoadCtrl2CommonIntf_metaObject;
}

igMetaObject *beNDMWLoadCtrl2CommonIntf_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadCtrl2CommonIntf_metaObject != 0) {
        ready = (g_beNDMWLoadCtrl2CommonIntf_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    beNDMWLoadCtrl2CommonIntf_EnsureRegistered();
done:
    return g_beNDMWLoadCtrl2CommonIntf_metaObject;
}

int beNDMWLoadCtrl2CommonIntf_GetVTable(void) {
    beNDMWLoadCtrl2CommonIntf obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    *(int **)&obj._vtable = &g_beNDMWLoadCtrl2CommonIntf_vtable[0];
    obj._slotSaveData = 0;
    obj._gameUseData = 0;
    obj._flagWork = 0;
    obj._mcUtilCtrl = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWLoadCtrl2CommonIntf_vtable[0];
    igSmartPointer_beNDMWMcUtilCtrl_Destruct((igSmartPointer<igObject> *)&obj._mcUtilCtrl, -1);
    igSmartPointer_beNDMWLoadSavePlWorkList_Destruct((igSmartPointer<igObject> *)&obj._flagWork, -1);
    igSmartPointer_beNDMWDegiDataList_Destruct((igSmartPointer<igObject> *)&obj._gameUseData, -1);
    igSmartPointer_beNDMWLoadSlotPlayerList_Destruct((igSmartPointer<igObject> *)&obj._slotSaveData, -1);
    beBaseInfoData_Destroy((beBaseInfoData *)&obj, 0);
    return vtable;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWLoadSlotPlayerList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWDegiDataList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_beNDMWLoadSavePlWorkList_Destruct(igSmartPointer<igObject> *self,int delete_storage) {
    if (self) {
        igObject *object = self->p;
        if (object) {
            --object->_refCount;
            if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        if ((short)delete_storage > 0) operator delete(self);
    }
    return self;
}

void beNDMWLoadCtrl2CommonIntf_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2CommonIntf_Register);
}

static igMetaObjectCallback g_beNDMWLoadCtrl2CommonIntf_callbackList[] = { beMessenger_EnsureRegistered, beSystem_EnsureRegistered, beBaseInfoRam_EnsureRegistered, igInsightCore_EnsureRegistered, beNDMWLoadSlotPlayerList_EnsureRegistered, beNDMWDegiDataList_EnsureRegistered, beNDMWLoadSavePlWorkList_EnsureRegistered, beNDMWMcUtilCtrl_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadCtrl2CommonIntf_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadCtrl2CommonIntf_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadCtrl2CommonIntf_GetMetaObject,
        "beNDMWLoadCtrl2CommonIntf",
        0x48, /* instance size */
        beNDMWLoadCtrl2CommonIntf_GetVTable,
        beNDMWLoadCtrl2CommonIntf_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadCtrl2CommonIntf_callbackList /* callback list */
    );
}

void beNDMWLoadCtrl2CommonIntf_GetMetaObject(void)
{
    beNDMWLoadCtrl2CommonIntf_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadCtrl2CommonIntf_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadCtrl2CommonIntf_fieldTable[] = {
    "_messenger",
    "_system",
    "_inforam",
    "_insight",
    "_slotSaveData",
    "_gameUseData",
    "_flagWork",
    "_nextStat",
    "_intfStat",
    "_mcUtilCtrl",
    "_kindHard",
    "_difficultMode",
    "_isTitle",
    "_utilUsePlNo",
};
static igMetaField **g_beNDMWLoadCtrl2CommonIntf_fieldHandles[] = {
    &g_beNDMWLoadCtrl2CommonIntf_messengerMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_systemMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_inforamMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_insightMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_slotSaveDataMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_gameUseDataMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_flagWorkMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_nextStatMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_intfStatMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_mcUtilCtrlMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_kindHardMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_difficultModeMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_isTitleMetaField,
    &g_beNDMWLoadCtrl2CommonIntf_utilUsePlNoMetaField,
};
static int g_beNDMWLoadCtrl2CommonIntf_fieldOffsets[] = {
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
};

void beNDMWLoadCtrl2CommonIntf_InitFields(void) {
    void **inheritedName;
    int nameIndex;
    int base;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWLoadCtrl2CommonIntf_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadCtrl2CommonIntf_ctorTable, 0xE);
    inheritedName = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    ((Gap::Core::igStringMetaField *)nameField)->setDefault("COMMONINTF");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadCtrl2CommonIntf_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, nameIndex, (igMetaField *)nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    void *messenger = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    void *system = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)system)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)system)->_refCounted = 0;
    void *inforam = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2));
    ((igObjectRefMetaField *)inforam)->_metaObject = (int)beBaseInfoRam_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)inforam)->_refCounted = 0;
    void *insight = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)insight)->_metaObject = (int)igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)insight)->_refCounted = 0;
    void *slotSaveData = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    ((igObjectRefMetaField *)slotSaveData)->_metaObject = (int)beNDMWLoadSlotPlayerList_GetOrCreateMetaObject();
    ((igRefMetaField *)slotSaveData)->_construct = 1;
    void *gameUseData = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    ((igObjectRefMetaField *)gameUseData)->_metaObject = (int)beNDMWDegiDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)gameUseData)->_construct = 1;
    void *flagWork = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6));
    ((igObjectRefMetaField *)flagWork)->_metaObject = (int)beNDMWLoadSavePlWorkList_GetOrCreateMetaObject();
    ((igRefMetaField *)flagWork)->_construct = 1;
    void *mcUtilCtrl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9));
    ((igObjectRefMetaField *)mcUtilCtrl)->_metaObject = (int)beNDMWMcUtilCtrl_GetOrCreateMetaObject();
    ((igRefMetaField *)mcUtilCtrl)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadCtrl2CommonIntf_fieldTable, g_beNDMWLoadCtrl2CommonIntf_fieldHandles, g_beNDMWLoadCtrl2CommonIntf_fieldOffsets, base);
}

