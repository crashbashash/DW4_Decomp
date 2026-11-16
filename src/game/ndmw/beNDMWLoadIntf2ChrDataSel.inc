igMetaObject *g_beNDMWLoadIntf2ChrDataSel_metaObject;
int g_beNDMWLoadIntf2ChrDataSel_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_comMdlCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_commonIntfMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_kindHardMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_oldPadDataMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_selMaxMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_ramNoMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_isCanselMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_isEndMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_selPointMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_mcSelPointMetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_st0MetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_st1MetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_st2MetaField;
igMetaField *g_beNDMWLoadIntf2ChrDataSel_st3MetaField;

igMetaObject *beNDMWLoadIntf2ChrDataSel_ResolveMetaObject(void)
{
    unsigned char ready;
    if (g_beNDMWLoadIntf2ChrDataSel_metaObject != 0) {
        ready = (g_beNDMWLoadIntf2ChrDataSel_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    beNDMWLoadIntf2ChrDataSel_EnsureRegistered();
done:
    return g_beNDMWLoadIntf2ChrDataSel_metaObject;
}

int beNDMWLoadIntf2ChrDataSel_GetVTable(void) {
    beNDMWLoadIntf2ChrDataSel obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2ChrDataSel_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWLoadIntf2ChrDataSel_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2ChrDataSel_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2ChrDataSel_callbackList[] = { beMessenger_EnsureRegistered, bePadManager_EnsureRegistered, beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered, beNDMWLoadCtrl2CommonIntf_EnsureRegistered, 0 };

void *beNDMWLoadIntf2ChrDataSel_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2ChrDataSel_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2ChrDataSel_GetMetaObject,
        "beNDMWLoadIntf2ChrDataSel",
        0x4c, /* instance size */
        beNDMWLoadIntf2ChrDataSel_GetVTable,
        beNDMWLoadIntf2ChrDataSel_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2ChrDataSel_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2ChrDataSel_GetMetaObject(void)
{
    beNDMWLoadIntf2ChrDataSel_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2ChrDataSel_ctorTable[] = {
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
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2ChrDataSel_fieldTable[] = {
    "_messenger",
    "_padManager",
    "_comMdlCtrl",
    "_commonIntf",
    "_kindHard",
    "_oldPadData",
    "_selMax",
    "_ramNo",
    "_isCansel",
    "_isEnd",
    "_selPoint",
    "_mcSelPoint",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2ChrDataSel_fieldHandles[] = {
    &g_beNDMWLoadIntf2ChrDataSel_messengerMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_padManagerMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_comMdlCtrlMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_commonIntfMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_kindHardMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_oldPadDataMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_selMaxMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_ramNoMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_isCanselMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_isEndMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_selPointMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_mcSelPointMetaField,
    &g_beNDMWLoadIntf2ChrDataSel_st0MetaField,
    &g_beNDMWLoadIntf2ChrDataSel_st1MetaField,
    &g_beNDMWLoadIntf2ChrDataSel_st2MetaField,
    &g_beNDMWLoadIntf2ChrDataSel_st3MetaField,
};
static int g_beNDMWLoadIntf2ChrDataSel_fieldOffsets[] = {
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
    52,
    56,
    60,
    64,
    68,
    72,
};

void beNDMWLoadIntf2ChrDataSel_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    igObjectRefMetaField *messenger;
    igObjectRefMetaField *padManager;
    igObjectRefMetaField *comMdlCtrl;
    igObjectRefMetaField *commonIntf;
    igMetaObject *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (igMetaObject *)(g_beNDMWLoadIntf2ChrDataSel_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2ChrDataSel_ctorTable, 0x10);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex(meta->_metaFields, inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    igStringMetaField_SetDefaultText(nameField, "CHRDATASEL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2ChrDataSel_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    messenger = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base));
    messenger->_metaObject = beMessenger_GetOrCreateMetaObject();
    messenger->_refCounted = 0;
    padManager = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 1));
    padManager->_metaObject = bePadManager_GetOrCreateMetaObject();
    padManager->_refCounted = 0;
    comMdlCtrl = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 2));
    comMdlCtrl->_metaObject = (int)beNDMWLoadIntf2ComMdlCtrl_GetOrCreateMetaObject();
    comMdlCtrl->_refCounted = 0;
    commonIntf = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(meta, base + 3));
    commonIntf->_metaObject = (int)beNDMWLoadCtrl2CommonIntf_GetOrCreateMetaObject();
    commonIntf->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2ChrDataSel_fieldTable, g_beNDMWLoadIntf2ChrDataSel_fieldHandles, g_beNDMWLoadIntf2ChrDataSel_fieldOffsets, base);
}

