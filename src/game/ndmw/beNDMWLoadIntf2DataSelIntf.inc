igMetaObject *g_beNDMWLoadIntf2DataSelIntf_metaObject;
int g_beNDMWLoadIntf2DataSelIntf_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_mcSelPointMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_svDataSelPointMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_comMdlCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_textOrderMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_commonIntfMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_mesWinMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_statDispMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isSaveAreaMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isUpStatWinMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isDownStatWinMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isSlotWinMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isSelCurMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_kindMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_plNoMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_mesKindMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_resultMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isEndMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_isCancelMetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_st0MetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_st1MetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_st2MetaField;
igMetaField *g_beNDMWLoadIntf2DataSelIntf_st3MetaField;

beNDMWLoadIntf2DataSelIntf *beNDMWLoadIntf2DataSelIntf_Create(int allocator) {
    beNDMWLoadIntf2DataSelIntf_EnsureRegistered();
    return (beNDMWLoadIntf2DataSelIntf *)igMetaObject_CreateInstance(g_beNDMWLoadIntf2DataSelIntf_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWLoadIntf2DataSelIntf_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2DataSelIntf_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWLoadIntf2DataSelIntf_EnsureRegistered();
    return g_beNDMWLoadIntf2DataSelIntf_metaObject;
}

int beNDMWLoadIntf2DataSelIntf_GetVTable(void) {
    beNDMWLoadIntf2DataSelIntf obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2DataSelIntf_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWLoadIntf2DataSelIntf_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2DataSelIntf_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2DataSelIntf_callbackList[] = { bePadManager_EnsureRegistered, beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered, beNDMWLoadIntf2TextOrder_EnsureRegistered, beNDMWLoadCtrl2CommonIntf_EnsureRegistered, beNDMWLoadIntf2MesWin_EnsureRegistered, beNDMWLoadIntf2DegiStateCtrl_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadIntf2DataSelIntf_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2DataSelIntf_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2DataSelIntf_GetMetaObject,
        "beNDMWLoadIntf2DataSelIntf",
        0x5c, /* instance size */
        beNDMWLoadIntf2DataSelIntf_GetVTable,
        beNDMWLoadIntf2DataSelIntf_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DataSelIntf_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2DataSelIntf_GetMetaObject(void)
{
    beNDMWLoadIntf2DataSelIntf_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2DataSelIntf_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2DataSelIntf_fieldTable[] = {
    "_mcSelPoint",
    "_svDataSelPoint",
    "_padManager",
    "_comMdlCtrl",
    "_textOrder",
    "_commonIntf",
    "_mesWin",
    "_statDisp",
    "_isSaveArea",
    "_isUpStatWin",
    "_isDownStatWin",
    "_isSlotWin",
    "_isSelCur",
    "_kind",
    "_plNo",
    "_mesKind",
    "_result",
    "_isEnd",
    "_isCancel",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2DataSelIntf_fieldHandles[] = {
    &g_beNDMWLoadIntf2DataSelIntf_mcSelPointMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_svDataSelPointMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_padManagerMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_comMdlCtrlMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_textOrderMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_commonIntfMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_mesWinMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_statDispMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isSaveAreaMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isUpStatWinMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isDownStatWinMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isSlotWinMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isSelCurMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_kindMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_plNoMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_mesKindMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_resultMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isEndMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_isCancelMetaField,
    &g_beNDMWLoadIntf2DataSelIntf_st0MetaField,
    &g_beNDMWLoadIntf2DataSelIntf_st1MetaField,
    &g_beNDMWLoadIntf2DataSelIntf_st2MetaField,
    &g_beNDMWLoadIntf2DataSelIntf_st3MetaField,
};
static int g_beNDMWLoadIntf2DataSelIntf_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    49,
    50,
    51,
    52,
    56,
    60,
    64,
    68,
    72,
    73,
    76,
    80,
    84,
    88,
};

void beNDMWLoadIntf2DataSelIntf_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    igObjectRefMetaField *padManager;
    igObjectRefMetaField *comMdlCtrl;
    igObjectRefMetaField *textOrder;
    igObjectRefMetaField *commonIntf;
    igObjectRefMetaField *mesWin;
    igObjectRefMetaField *statDisp;
    igMetaObject *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (igMetaObject *)(g_beNDMWLoadIntf2DataSelIntf_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2DataSelIntf_ctorTable, 0x17);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)meta->_metaFields, (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    ((Gap::Core::igStringMetaField *)nameField)->setDefault("DATASELINTF");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2DataSelIntf_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, (igMetaField *)nameField);
    nameField->release();
    padManager = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 2));
    padManager->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    padManager->_refCounted = 0;
    comMdlCtrl = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 3));
    comMdlCtrl->_metaObject = (int)beNDMWLoadIntf2ComMdlCtrl_GetOrCreateMetaObject();
    comMdlCtrl->_refCounted = 0;
    textOrder = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 4));
    textOrder->_metaObject = (int)beNDMWLoadIntf2TextOrder_GetOrCreateMetaObject();
    textOrder->_refCounted = 0;
    commonIntf = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 5));
    commonIntf->_metaObject = (int)beNDMWLoadCtrl2CommonIntf_GetOrCreateMetaObject();
    commonIntf->_refCounted = 0;
    mesWin = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 6));
    mesWin->_metaObject = (int)beNDMWLoadIntf2MesWin_GetOrCreateMetaObject();
    mesWin->_refCounted = 0;
    statDisp = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 7));
    statDisp->_metaObject = (int)beNDMWLoadIntf2DegiStateCtrl_GetOrCreateMetaObject();
    statDisp->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2DataSelIntf_fieldTable, g_beNDMWLoadIntf2DataSelIntf_fieldHandles, g_beNDMWLoadIntf2DataSelIntf_fieldOffsets, base);
}

