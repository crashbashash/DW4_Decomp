igMetaObject *g_beNDMWLoadIntf2CtrlData_metaObject;
int g_beNDMWLoadIntf2CtrlData_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2CtrlData_isRunMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isRdyMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isEntryMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isCtrlMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isCanselMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isMesWinMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isSystemMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isNoSelMdlMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_newLoadSelMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isNewMakeMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_isRdyCancelMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_oldPadDataMetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_st0MetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_st1MetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_st2MetaField;
igMetaField *g_beNDMWLoadIntf2CtrlData_st3MetaField;
igMetaEnum *g_beNDMWLoadIntf2CtrlData_messageMetaEnum;

beNDMWLoadIntf2CtrlData *beNDMWLoadIntf2CtrlData_Create(int allocator) {
    beNDMWLoadIntf2CtrlData_EnsureRegistered();
    return (beNDMWLoadIntf2CtrlData *)igMetaObject_CreateInstance(g_beNDMWLoadIntf2CtrlData_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWLoadIntf2CtrlData_ResolveMetaObject(void) {
    bool ok;
    if (g_beNDMWLoadIntf2CtrlData_metaObject == 0) goto make;
    ok = !!(g_beNDMWLoadIntf2CtrlData_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWLoadIntf2CtrlData_EnsureRegistered();
done:;
    return g_beNDMWLoadIntf2CtrlData_metaObject;
}

int beNDMWLoadIntf2CtrlData_GetVTable(void) {
    beNDMWLoadIntf2CtrlData obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2CtrlData_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWLoadIntf2CtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2CtrlData_Register);
}

CallbackArray *beNDMWLoadIntf2CtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2CtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2CtrlData_GetMetaObject,
        "beNDMWLoadIntf2CtrlData",
        0x34, /* instance size */
        beNDMWLoadIntf2CtrlData_GetVTable,
        beNDMWLoadIntf2CtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLoadIntf2CtrlData_GetMetaObject(void)
{
    beNDMWLoadIntf2CtrlData_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2CtrlData_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2CtrlData_fieldTable[] = {
    "_isRun",
    "_isRdy",
    "_isEntry",
    "_isCtrl",
    "_isCansel",
    "_isMesWin",
    "_isSystem",
    "_isNoSelMdl",
    "_newLoadSel",
    "_isNewMake",
    "_isRdyCancel",
    "_oldPadData",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadIntf2CtrlData_fieldHandles[] = {
    &g_beNDMWLoadIntf2CtrlData_isRunMetaField,
    &g_beNDMWLoadIntf2CtrlData_isRdyMetaField,
    &g_beNDMWLoadIntf2CtrlData_isEntryMetaField,
    &g_beNDMWLoadIntf2CtrlData_isCtrlMetaField,
    &g_beNDMWLoadIntf2CtrlData_isCanselMetaField,
    &g_beNDMWLoadIntf2CtrlData_isMesWinMetaField,
    &g_beNDMWLoadIntf2CtrlData_isSystemMetaField,
    &g_beNDMWLoadIntf2CtrlData_isNoSelMdlMetaField,
    &g_beNDMWLoadIntf2CtrlData_newLoadSelMetaField,
    &g_beNDMWLoadIntf2CtrlData_isNewMakeMetaField,
    &g_beNDMWLoadIntf2CtrlData_isRdyCancelMetaField,
    &g_beNDMWLoadIntf2CtrlData_oldPadDataMetaField,
    &g_beNDMWLoadIntf2CtrlData_st0MetaField,
    &g_beNDMWLoadIntf2CtrlData_st1MetaField,
    &g_beNDMWLoadIntf2CtrlData_st2MetaField,
    &g_beNDMWLoadIntf2CtrlData_st3MetaField,
};
static int g_beNDMWLoadIntf2CtrlData_fieldOffsets[] = {
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    28,
    29,
    32,
    36,
    40,
    44,
    48,
};

void beNDMWLoadIntf2CtrlData_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWLoadIntf2CtrlData_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2CtrlData_ctorTable, 0x10);
    inheritedName = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((char *)((igMetaObject *)meta)->_metaFields, (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    igStringMetaField_SetDefaultText((igMetaField *)nameField, "CTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2CtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, nameIndex, (igMetaField *)nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2CtrlData_fieldTable, g_beNDMWLoadIntf2CtrlData_fieldHandles, g_beNDMWLoadIntf2CtrlData_fieldOffsets, base);
}

static const char *g_beNDMWLoadIntf2CtrlData_messageNames[] = {
    "GENERATE",
    "LINKCOMMON",
    "ISENTRY",
    "ISRDY",
    "ONCTRL",
    "OFFCTRL",
    "SETSELECT_DATA",
    "SETDIFFICULTMAX",
};
static int g_beNDMWLoadIntf2CtrlData_messageValues[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
};

igMetaEnum *LoadIntf2Message_GetMetaEnum(void) {
    if (g_beNDMWLoadIntf2CtrlData_messageMetaEnum == 0) {
        g_beNDMWLoadIntf2CtrlData_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWLoadIntf2CtrlData_messageNames, g_beNDMWLoadIntf2CtrlData_messageValues, 8);
    }
    return g_beNDMWLoadIntf2CtrlData_messageMetaEnum;
}

