igMetaObject *g_beNDMWLoadIntf2SelSlot_metaObject;
int g_beNDMWLoadIntf2SelSlot_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2SelSlot_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_comMdlCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_textOrderMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_commonIntfMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_kindHardMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_oldPadDataMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_selMaxMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_ramNoMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_isOpenMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_isSelectMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_isCanselMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_isReOpenReqMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_isEndMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_selPointMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_mcSelPointMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_modeMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_mcStatMetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_st0MetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_st1MetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_st2MetaField;
igMetaField *g_beNDMWLoadIntf2SelSlot_st3MetaField;

beNDMWLoadIntf2SelSlot *beNDMWLoadIntf2SelSlot_Create(int allocator) {
    beNDMWLoadIntf2SelSlot_EnsureRegistered();
    return (beNDMWLoadIntf2SelSlot *)igMetaObject_CreateInstance(g_beNDMWLoadIntf2SelSlot_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWLoadIntf2SelSlot_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadIntf2SelSlot_metaObject != 0) {
        ready = (g_beNDMWLoadIntf2SelSlot_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    beNDMWLoadIntf2SelSlot_EnsureRegistered();
done:
    return g_beNDMWLoadIntf2SelSlot_metaObject;
}

int beNDMWLoadIntf2SelSlot_GetVTable(void) {
    beNDMWLoadIntf2SelSlot obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2SelSlot_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWLoadIntf2SelSlot_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2SelSlot_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2SelSlot_callbackList[] = { beMessenger_EnsureRegistered, bePadManager_EnsureRegistered, beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered, beNDMWLoadIntf2TextOrder_EnsureRegistered, beNDMWLoadCtrl2CommonIntf_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadIntf2SelSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2SelSlot_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2SelSlot_GetMetaObject,
        "beNDMWLoadIntf2SelSlot",
        0x5c, /* instance size */
        beNDMWLoadIntf2SelSlot_GetVTable,
        beNDMWLoadIntf2SelSlot_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2SelSlot_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2SelSlot_GetMetaObject(void)
{
    beNDMWLoadIntf2SelSlot_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2SelSlot_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
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
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2SelSlot_fieldTable[] = {
    "_messenger",
    "_padManager",
    "_comMdlCtrl",
    "_textOrder",
    "_commonIntf",
    "_kindHard",
    "_oldPadData",
    "_selMax",
    "_ramNo",
    "_isOpen",
    "_isSelect",
    "_isCansel",
    "_isReOpenReq",
    "_isEnd",
    "_selPoint",
    "_mcSelPoint",
    "_mode",
    "_mcStat",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2SelSlot_fieldHandles[] = {
    &g_beNDMWLoadIntf2SelSlot_messengerMetaField,
    &g_beNDMWLoadIntf2SelSlot_padManagerMetaField,
    &g_beNDMWLoadIntf2SelSlot_comMdlCtrlMetaField,
    &g_beNDMWLoadIntf2SelSlot_textOrderMetaField,
    &g_beNDMWLoadIntf2SelSlot_commonIntfMetaField,
    &g_beNDMWLoadIntf2SelSlot_kindHardMetaField,
    &g_beNDMWLoadIntf2SelSlot_oldPadDataMetaField,
    &g_beNDMWLoadIntf2SelSlot_selMaxMetaField,
    &g_beNDMWLoadIntf2SelSlot_ramNoMetaField,
    &g_beNDMWLoadIntf2SelSlot_isOpenMetaField,
    &g_beNDMWLoadIntf2SelSlot_isSelectMetaField,
    &g_beNDMWLoadIntf2SelSlot_isCanselMetaField,
    &g_beNDMWLoadIntf2SelSlot_isReOpenReqMetaField,
    &g_beNDMWLoadIntf2SelSlot_isEndMetaField,
    &g_beNDMWLoadIntf2SelSlot_selPointMetaField,
    &g_beNDMWLoadIntf2SelSlot_mcSelPointMetaField,
    &g_beNDMWLoadIntf2SelSlot_modeMetaField,
    &g_beNDMWLoadIntf2SelSlot_mcStatMetaField,
    &g_beNDMWLoadIntf2SelSlot_st0MetaField,
    &g_beNDMWLoadIntf2SelSlot_st1MetaField,
    &g_beNDMWLoadIntf2SelSlot_st2MetaField,
    &g_beNDMWLoadIntf2SelSlot_st3MetaField,
};
static int g_beNDMWLoadIntf2SelSlot_fieldOffsets[] = {
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
    53,
    54,
    55,
    56,
    60,
    64,
    68,
    72,
    76,
    80,
    84,
    88,
};

void beNDMWLoadIntf2SelSlot_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *messenger;
    void *padManager;
    void *comMdlCtrl;
    void *textOrder;
    void *commonIntf;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWLoadIntf2SelSlot_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2SelSlot_ctorTable, 0x16);
    inheritedName = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    igStringMetaField_SetDefaultText((igMetaField *)nameField, "SELSLOT");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2SelSlot_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, nameIndex, (igMetaField *)nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    messenger = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    padManager = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)padManager)->_refCounted = 0;
    comMdlCtrl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2));
    ((igObjectRefMetaField *)comMdlCtrl)->_metaObject = (int)beNDMWLoadIntf2ComMdlCtrl_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)comMdlCtrl)->_refCounted = 0;
    textOrder = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3));
    ((igObjectRefMetaField *)textOrder)->_metaObject = (int)beNDMWLoadIntf2TextOrder_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)textOrder)->_refCounted = 0;
    commonIntf = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4));
    ((igObjectRefMetaField *)commonIntf)->_metaObject = (int)beNDMWLoadCtrl2CommonIntf_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)commonIntf)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2SelSlot_fieldTable, g_beNDMWLoadIntf2SelSlot_fieldHandles, g_beNDMWLoadIntf2SelSlot_fieldOffsets, base);
}

