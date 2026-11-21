igMetaObject *g_beNDMWLoadIntf2Diffselect_metaObject;
int g_beNDMWLoadIntf2Diffselect_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2Diffselect_selectPointMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_maxSelMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_plNoMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_resultMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_kindMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_isEndMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_isCancelMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_comMdlCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_textOrderMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_commonIntfMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_mesWinMetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_st0MetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_st1MetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_st2MetaField;
igMetaField *g_beNDMWLoadIntf2Diffselect_st3MetaField;

beNDMWLoadIntf2Diffselect *beNDMWLoadIntf2Diffselect_Create(int allocator) {
    beNDMWLoadIntf2Diffselect_EnsureRegistered();
    return (beNDMWLoadIntf2Diffselect *)igMetaObject_CreateInstance(g_beNDMWLoadIntf2Diffselect_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWLoadIntf2Diffselect_ResolveMetaObject(void)
{
    igMetaObject *g = g_beNDMWLoadIntf2Diffselect_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWLoadIntf2Diffselect_EnsureRegistered();
    return g_beNDMWLoadIntf2Diffselect_metaObject;
}

int beNDMWLoadIntf2Diffselect_GetVTable(void) {
    beNDMWLoadIntf2Diffselect obj;
    int vtable;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    obj._name = 0;
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2Diffselect_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (&obj._name != 0) {
        releaseString((const char *)obj._name);
    }
    return vtable;
}

void beNDMWLoadIntf2Diffselect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2Diffselect_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2Diffselect_callbackList[] = { bePadManager_EnsureRegistered, beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered, beNDMWLoadIntf2TextOrder_EnsureRegistered, beNDMWLoadCtrl2CommonIntf_EnsureRegistered, beNDMWLoadIntf2MesWin_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadIntf2Diffselect_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2Diffselect_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2Diffselect_GetMetaObject,
        "beNDMWLoadIntf2Diffselect",
        0x4c, /* instance size */
        beNDMWLoadIntf2Diffselect_GetVTable,
        beNDMWLoadIntf2Diffselect_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2Diffselect_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2Diffselect_GetMetaObject(void)
{
    beNDMWLoadIntf2Diffselect_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2Diffselect_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2Diffselect_fieldTable[] = {
    "_selectPoint",
    "_maxSel",
    "_plNo",
    "_result",
    "_kind",
    "_isEnd",
    "_isCancel",
    "_padManager",
    "_comMdlCtrl",
    "_textOrder",
    "_commonIntf",
    "_mesWin",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2Diffselect_fieldHandles[] = {
    &g_beNDMWLoadIntf2Diffselect_selectPointMetaField,
    &g_beNDMWLoadIntf2Diffselect_maxSelMetaField,
    &g_beNDMWLoadIntf2Diffselect_plNoMetaField,
    &g_beNDMWLoadIntf2Diffselect_resultMetaField,
    &g_beNDMWLoadIntf2Diffselect_kindMetaField,
    &g_beNDMWLoadIntf2Diffselect_isEndMetaField,
    &g_beNDMWLoadIntf2Diffselect_isCancelMetaField,
    &g_beNDMWLoadIntf2Diffselect_padManagerMetaField,
    &g_beNDMWLoadIntf2Diffselect_comMdlCtrlMetaField,
    &g_beNDMWLoadIntf2Diffselect_textOrderMetaField,
    &g_beNDMWLoadIntf2Diffselect_commonIntfMetaField,
    &g_beNDMWLoadIntf2Diffselect_mesWinMetaField,
    &g_beNDMWLoadIntf2Diffselect_st0MetaField,
    &g_beNDMWLoadIntf2Diffselect_st1MetaField,
    &g_beNDMWLoadIntf2Diffselect_st2MetaField,
    &g_beNDMWLoadIntf2Diffselect_st3MetaField,
};
static int g_beNDMWLoadIntf2Diffselect_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    37,
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

void beNDMWLoadIntf2Diffselect_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *padManager;
    void *comMdlCtrl;
    void *textOrder;
    void *commonIntf;
    void *mesWin;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWLoadIntf2Diffselect_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2Diffselect_ctorTable, 0x10);
    inheritedName = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    ((Gap::Core::igStringMetaField *)nameField)->setDefault("DIFFSELECT");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2Diffselect_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, nameIndex, (igMetaField *)nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    padManager = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)padManager)->_refCounted = 0;
    comMdlCtrl = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8));
    ((igObjectRefMetaField *)comMdlCtrl)->_metaObject = (int)beNDMWLoadIntf2ComMdlCtrl_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)comMdlCtrl)->_refCounted = 0;
    textOrder = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9));
    ((igObjectRefMetaField *)textOrder)->_metaObject = (int)beNDMWLoadIntf2TextOrder_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)textOrder)->_refCounted = 0;
    commonIntf = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xA));
    ((igObjectRefMetaField *)commonIntf)->_metaObject = (int)beNDMWLoadCtrl2CommonIntf_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)commonIntf)->_refCounted = 0;
    mesWin = (void *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xB));
    ((igObjectRefMetaField *)mesWin)->_metaObject = (int)beNDMWLoadIntf2MesWin_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)mesWin)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2Diffselect_fieldTable, g_beNDMWLoadIntf2Diffselect_fieldHandles, g_beNDMWLoadIntf2Diffselect_fieldOffsets, base);
}

