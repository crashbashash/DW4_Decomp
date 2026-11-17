igMetaObject *g_beNDMWLoadIntf2MesWin_metaObject;
int g_beNDMWLoadIntf2MesWin_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2MesWin_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_textOrderMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isWinOpenMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isWinCloseMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isSelectMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isSystemMesMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isMesEraseMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isMesComMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_isDispMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_kindCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_statCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_ramNoMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_curPointMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_mesNoMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_sysMesNoMetaField;
igMetaField *g_beNDMWLoadIntf2MesWin_sysStatMetaField;

beNDMWLoadIntf2MesWin *beNDMWLoadIntf2MesWin_Create(int allocator) {
    beNDMWLoadIntf2MesWin_EnsureRegistered();
    return (beNDMWLoadIntf2MesWin *)igMetaObject_CreateInstance(g_beNDMWLoadIntf2MesWin_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWLoadIntf2MesWin_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadIntf2MesWin_metaObject == 0) {
        g_beNDMWLoadIntf2MesWin_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWLoadIntf2MesWin_metaObject;
}

void *beNDMWLoadIntf2MesWin_GetReadyMetaObject(void) {
    unsigned char b;
    if (g_beNDMWLoadIntf2MesWin_metaObject != 0) {
        b = (g_beNDMWLoadIntf2MesWin_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWLoadIntf2MesWin_EnsureRegistered();
done:
    return g_beNDMWLoadIntf2MesWin_metaObject;
}

int beNDMWLoadIntf2MesWin_GetVTable(void) {
    beNDMWLoadIntf2MesWin obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2MesWin_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWLoadIntf2MesWin_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2MesWin_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2MesWin_callbackList[] = { beMessenger_EnsureRegistered, bePadManager_EnsureRegistered, beNDMWLoadIntf2TextOrder_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadIntf2MesWin_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2MesWin_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2MesWin_GetMetaObject,
        "beNDMWLoadIntf2MesWin",
        0x40, /* instance size */
        beNDMWLoadIntf2MesWin_GetVTable,
        beNDMWLoadIntf2MesWin_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2MesWin_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2MesWin_GetMetaObject(void)
{
    beNDMWLoadIntf2MesWin_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2MesWin_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2MesWin_fieldTable[] = {
    "_messenger",
    "_padManager",
    "_textOrder",
    "_isWinOpen",
    "_isWinClose",
    "_isSelect",
    "_isSystemMes",
    "_isMesErase",
    "_isMesCom",
    "_isCtrl",
    "_isDisp",
    "_kindCtrl",
    "_statCtrl",
    "_ramNo",
    "_curPoint",
    "_mesNo",
    "_sysMesNo",
    "_sysStat",
};
static igMetaField **g_beNDMWLoadIntf2MesWin_fieldHandles[] = {
    &g_beNDMWLoadIntf2MesWin_messengerMetaField,
    &g_beNDMWLoadIntf2MesWin_padManagerMetaField,
    &g_beNDMWLoadIntf2MesWin_textOrderMetaField,
    &g_beNDMWLoadIntf2MesWin_isWinOpenMetaField,
    &g_beNDMWLoadIntf2MesWin_isWinCloseMetaField,
    &g_beNDMWLoadIntf2MesWin_isSelectMetaField,
    &g_beNDMWLoadIntf2MesWin_isSystemMesMetaField,
    &g_beNDMWLoadIntf2MesWin_isMesEraseMetaField,
    &g_beNDMWLoadIntf2MesWin_isMesComMetaField,
    &g_beNDMWLoadIntf2MesWin_isCtrlMetaField,
    &g_beNDMWLoadIntf2MesWin_isDispMetaField,
    &g_beNDMWLoadIntf2MesWin_kindCtrlMetaField,
    &g_beNDMWLoadIntf2MesWin_statCtrlMetaField,
    &g_beNDMWLoadIntf2MesWin_ramNoMetaField,
    &g_beNDMWLoadIntf2MesWin_curPointMetaField,
    &g_beNDMWLoadIntf2MesWin_mesNoMetaField,
    &g_beNDMWLoadIntf2MesWin_sysMesNoMetaField,
    &g_beNDMWLoadIntf2MesWin_sysStatMetaField,
};
static int g_beNDMWLoadIntf2MesWin_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    29,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    40,
    44,
    48,
    52,
    56,
    60,
};

void beNDMWLoadIntf2MesWin_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    igObjectRefMetaField *messenger;
    igObjectRefMetaField *padManager;
    igObjectRefMetaField *textOrder;
    igMetaObject *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (igMetaObject *)(g_beNDMWLoadIntf2MesWin_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2MesWin_ctorTable, 0x12);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)meta->_metaFields, (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    igStringMetaField_SetDefaultText((igMetaField *)nameField, "MESWIN");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2MesWin_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, (igMetaField *)nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    messenger = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base));
    messenger->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    messenger->_refCounted = 0;
    padManager = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 1));
    padManager->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    padManager->_refCounted = 0;
    textOrder = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 2));
    textOrder->_metaObject = (int)beNDMWLoadIntf2TextOrder_GetOrCreateMetaObject();
    textOrder->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2MesWin_fieldTable, g_beNDMWLoadIntf2MesWin_fieldHandles, g_beNDMWLoadIntf2MesWin_fieldOffsets, base);
}

