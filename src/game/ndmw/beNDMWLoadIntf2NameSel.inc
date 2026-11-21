igMetaObject *g_beNDMWLoadIntf2NameSel_metaObject;
int g_beNDMWLoadIntf2NameSel_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2NameSel_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_comMdlCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_textOrderMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_ramNoMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_selDataNoMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_langIDMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_tateMaxMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_tateMinMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_tatePointMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_yokoPointMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_yokoCurPosMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_oldPadDataMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_nameMojiMaxMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_nameCurPosMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isEndMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isMakeNameMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isQuestionMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isAnswerMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isNameOKMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_isSideCurMetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_st0MetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_st1MetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_st2MetaField;
igMetaField *g_beNDMWLoadIntf2NameSel_st3MetaField;

beNDMWLoadIntf2NameSel *beNDMWLoadIntf2NameSel_Create(int allocator) {
    beNDMWLoadIntf2NameSel_EnsureRegistered();
    return (beNDMWLoadIntf2NameSel *)igMetaObject_CreateInstance(g_beNDMWLoadIntf2NameSel_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWLoadIntf2NameSel_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2NameSel_metaObject;
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (exceptions on); `if (ready = ...)` folds it away */
        ready = g->_validity & 4;
        if (ready != false) goto end;
    }
    beNDMWLoadIntf2NameSel_EnsureRegistered();
end:
    return g_beNDMWLoadIntf2NameSel_metaObject;
}

int beNDMWLoadIntf2NameSel_GetVTable(void) {
    beNDMWLoadIntf2NameSel obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2NameSel_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWLoadIntf2NameSel_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2NameSel_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2NameSel_callbackList[] = { beMessenger_EnsureRegistered, bePadManager_EnsureRegistered, beNDMWLoadIntf2ComMdlCtrl_EnsureRegistered, beNDMWLoadIntf2TextOrder_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadIntf2NameSel_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2NameSel_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2NameSel_GetMetaObject,
        "beNDMWLoadIntf2NameSel",
        0x120, /* instance size */
        beNDMWLoadIntf2NameSel_GetVTable,
        beNDMWLoadIntf2NameSel_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2NameSel_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2NameSel_GetMetaObject(void)
{
    beNDMWLoadIntf2NameSel_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2NameSel_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
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
};
static const char *g_beNDMWLoadIntf2NameSel_fieldTable[] = {
    "_messenger",
    "_padManager",
    "_comMdlCtrl",
    "_textOrder",
    "_ramNo",
    "_selDataNo",
    "_langID",
    "_tateMax",
    "_tateMin",
    "_tatePoint",
    "_yokoPoint",
    "_yokoCurPos",
    "_oldPadData",
    "_nameMojiMax",
    "_nameCurPos",
    "_isEnd",
    "_isMakeName",
    "_isQuestion",
    "_isAnswer",
    "_isNameOK",
    "_isSideCur",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2NameSel_fieldHandles[] = {
    &g_beNDMWLoadIntf2NameSel_messengerMetaField,
    &g_beNDMWLoadIntf2NameSel_padManagerMetaField,
    &g_beNDMWLoadIntf2NameSel_comMdlCtrlMetaField,
    &g_beNDMWLoadIntf2NameSel_textOrderMetaField,
    &g_beNDMWLoadIntf2NameSel_ramNoMetaField,
    &g_beNDMWLoadIntf2NameSel_selDataNoMetaField,
    &g_beNDMWLoadIntf2NameSel_langIDMetaField,
    &g_beNDMWLoadIntf2NameSel_tateMaxMetaField,
    &g_beNDMWLoadIntf2NameSel_tateMinMetaField,
    &g_beNDMWLoadIntf2NameSel_tatePointMetaField,
    &g_beNDMWLoadIntf2NameSel_yokoPointMetaField,
    &g_beNDMWLoadIntf2NameSel_yokoCurPosMetaField,
    &g_beNDMWLoadIntf2NameSel_oldPadDataMetaField,
    &g_beNDMWLoadIntf2NameSel_nameMojiMaxMetaField,
    &g_beNDMWLoadIntf2NameSel_nameCurPosMetaField,
    &g_beNDMWLoadIntf2NameSel_isEndMetaField,
    &g_beNDMWLoadIntf2NameSel_isMakeNameMetaField,
    &g_beNDMWLoadIntf2NameSel_isQuestionMetaField,
    &g_beNDMWLoadIntf2NameSel_isAnswerMetaField,
    &g_beNDMWLoadIntf2NameSel_isNameOKMetaField,
    &g_beNDMWLoadIntf2NameSel_isSideCurMetaField,
    &g_beNDMWLoadIntf2NameSel_st0MetaField,
    &g_beNDMWLoadIntf2NameSel_st1MetaField,
    &g_beNDMWLoadIntf2NameSel_st2MetaField,
    &g_beNDMWLoadIntf2NameSel_st3MetaField,
};
static int g_beNDMWLoadIntf2NameSel_fieldOffsets[] = {
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
    72,
    76,
    77,
    78,
    79,
    80,
    81,
    84,
    88,
    92,
    96,
};

void beNDMWLoadIntf2NameSel_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *messenger;
    void *padManager;
    void *comMdlCtrl;
    void *textOrder;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWLoadIntf2NameSel_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2NameSel_ctorTable, 0x19);
    inheritedName = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    ((Gap::Core::igStringMetaField *)nameField)->setDefault("NAMESEL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2NameSel_nameExternalEnumStorage);
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
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xE)))->setDefault(-1);
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2NameSel_fieldTable, g_beNDMWLoadIntf2NameSel_fieldHandles, g_beNDMWLoadIntf2NameSel_fieldOffsets, base);
}

