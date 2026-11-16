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

void beNDMWLoadCtrl2CommonIntf_Create(int allocator) {
    beNDMWLoadCtrl2CommonIntf_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadCtrl2CommonIntf_metaObject, allocator);
}

igMetaObject *beNDMWLoadCtrl2CommonIntf_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadCtrl2CommonIntf_metaObject == 0) {
        g_beNDMWLoadCtrl2CommonIntf_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    struct Obj_3c4cc0 obj;
    int temp_s3;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.vt = (&g_beNDMWLoadCtrl2CommonIntf_vtable[0]);
    obj.f20 = 0;
    obj.f24 = 0;
    obj.f28 = 0;
    obj.f34 = 0;
    temp_s3 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beNDMWLoadCtrl2CommonIntf_vtable[0]);
    FUN_003b2a10((igSmartPointer<igObject> *)&obj.f34, -1);
    FUN_003c4e80((igSmartPointer<igObject> *)&obj.f28, -1);
    FUN_003c4e00((igSmartPointer<igObject> *)&obj.f24, -1);
    FUN_003c4d80((igSmartPointer<igObject> *)&obj.f20, -1);
    FUN_00344030(&obj, 0);
    return temp_s3;
}

igSmartPointer<igObject> *FUN_003c4d80(igSmartPointer<igObject> *self,int delete_storage) {
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

igSmartPointer<igObject> *FUN_003c4e00(igSmartPointer<igObject> *self,int delete_storage) {
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

igSmartPointer<igObject> *FUN_003c4e80(igSmartPointer<igObject> *self,int delete_storage) {
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

void beNDMWLoadCtrl2CommonIntf_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2CommonIntf_Register);
}

static igMetaObjectCallback g_beNDMWLoadCtrl2CommonIntf_callbackList[] = { beMessenger_EnsureRegistered, beSystem_EnsureRegistered, beBaseInfoRam_EnsureRegistered, igInsightCore_EnsureRegistered, beNDMWLoadSlotPlayerList_EnsureRegistered, beNDMWDegiDataList_EnsureRegistered, beNDMWLoadSavePlWorkList_EnsureRegistered, beNDMWMcUtilCtrl_EnsureRegistered, 0 };

void *beNDMWLoadCtrl2CommonIntf_Register(void) {
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
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadCtrl2CommonIntf_ctorTable, 0xE);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, inheritedName);
    nameField = (igStringMetaField *)(((DW4VC_84_1 *)(inheritedName))->vX((int)(1)));
    igStringMetaField_SetDefaultText(nameField, "COMMONINTF");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadCtrl2CommonIntf_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    void *messenger = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    void *system = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)system)->_metaObject = beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)system)->_refCounted = 0;
    void *inforam = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)inforam)->_metaObject = beBaseInfoRam_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)inforam)->_refCounted = 0;
    void *insight = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)insight)->_metaObject = igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)insight)->_refCounted = 0;
    void *slotSaveData = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)slotSaveData)->_metaObject = (int)beNDMWLoadSlotPlayerList_GetOrCreateMetaObject();
    ((igRefMetaField *)slotSaveData)->_construct = 1;
    void *gameUseData = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)gameUseData)->_metaObject = (int)beNDMWDegiDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)gameUseData)->_construct = 1;
    void *flagWork = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)flagWork)->_metaObject = (int)beNDMWLoadSavePlWorkList_GetOrCreateMetaObject();
    ((igRefMetaField *)flagWork)->_construct = 1;
    void *mcUtilCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)mcUtilCtrl)->_metaObject = (int)beNDMWMcUtilCtrl_GetOrCreateMetaObject();
    ((igRefMetaField *)mcUtilCtrl)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadCtrl2CommonIntf_fieldTable, g_beNDMWLoadCtrl2CommonIntf_fieldHandles, g_beNDMWLoadCtrl2CommonIntf_fieldOffsets, base);
}

