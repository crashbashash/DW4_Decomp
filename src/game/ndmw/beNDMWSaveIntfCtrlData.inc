igMetaObject *g_beNDMWSaveIntfCtrlData_metaObject;
int g_beNDMWSaveIntfCtrlData_nameExternalEnumStorage;
igMetaField *g_beNDMWSaveIntfCtrlData_isRunMetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_isRdyMetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_isEntryMetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_isCtrlMetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_isCanselMetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_isMesWinMetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_isSystemMetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_isOneSaveMetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_newLoadSelMetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_isCharMakeMetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_oldPadDataMetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_st0MetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_st1MetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_st2MetaField;
igMetaField *g_beNDMWSaveIntfCtrlData_st3MetaField;
igMetaEnum *g_beNDMWSaveIntfCtrlData_messageMetaEnum;

beNDMWSaveIntfCtrlData *beNDMWSaveIntfCtrlData_Create(int allocator) {
    beNDMWSaveIntfCtrlData_EnsureRegistered();
    return (beNDMWSaveIntfCtrlData *)igMetaObject_CreateInstance(g_beNDMWSaveIntfCtrlData_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWSaveIntfCtrlData_GetMetaObject(void) {
    bool ok;
    if (g_beNDMWSaveIntfCtrlData_metaObject == 0) goto make;
    ok = !!(g_beNDMWSaveIntfCtrlData_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWSaveIntfCtrlData_EnsureRegistered();
done:;
    return g_beNDMWSaveIntfCtrlData_metaObject;
}

int beNDMWSaveIntfCtrlData_GetVTable(void) {
    beNDMWSaveIntfCtrlData obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWSaveIntfCtrlData_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWSaveIntfCtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfCtrlData_Register);
}

CallbackArray *beNDMWSaveIntfCtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveIntfCtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWSaveIntfCtrlData_GetMetaObjectFunction,
        "beNDMWSaveIntfCtrlData",
        0x34, /* instance size */
        beNDMWSaveIntfCtrlData_GetVTable,
        beNDMWSaveIntfCtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWSaveIntfCtrlData_GetMetaObjectFunction(void)
{
    beNDMWSaveIntfCtrlData_GetMetaObject();
}

static FieldFactory g_beNDMWSaveIntfCtrlData_ctorTable[] = {
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
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWSaveIntfCtrlData_fieldTable[] = {
    "_isRun",
    "_isRdy",
    "_isEntry",
    "_isCtrl",
    "_isCansel",
    "_isMesWin",
    "_isSystem",
    "_isOneSave",
    "_newLoadSel",
    "_isCharMake",
    "_oldPadData",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWSaveIntfCtrlData_fieldHandles[] = {
    &g_beNDMWSaveIntfCtrlData_isRunMetaField,
    &g_beNDMWSaveIntfCtrlData_isRdyMetaField,
    &g_beNDMWSaveIntfCtrlData_isEntryMetaField,
    &g_beNDMWSaveIntfCtrlData_isCtrlMetaField,
    &g_beNDMWSaveIntfCtrlData_isCanselMetaField,
    &g_beNDMWSaveIntfCtrlData_isMesWinMetaField,
    &g_beNDMWSaveIntfCtrlData_isSystemMetaField,
    &g_beNDMWSaveIntfCtrlData_isOneSaveMetaField,
    &g_beNDMWSaveIntfCtrlData_newLoadSelMetaField,
    &g_beNDMWSaveIntfCtrlData_isCharMakeMetaField,
    &g_beNDMWSaveIntfCtrlData_oldPadDataMetaField,
    &g_beNDMWSaveIntfCtrlData_st0MetaField,
    &g_beNDMWSaveIntfCtrlData_st1MetaField,
    &g_beNDMWSaveIntfCtrlData_st2MetaField,
    &g_beNDMWSaveIntfCtrlData_st3MetaField,
};
static int g_beNDMWSaveIntfCtrlData_fieldOffsets[] = {
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
    32,
    36,
    40,
    44,
    48,
};

void beNDMWSaveIntfCtrlData_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWSaveIntfCtrlData_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWSaveIntfCtrlData_ctorTable, 0xF);
    inheritedName = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    ((Gap::Core::igStringMetaField *)nameField)->setDefault("CTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWSaveIntfCtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, nameIndex, (igMetaField *)nameField);
    nameField->release();
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWSaveIntfCtrlData_fieldTable, g_beNDMWSaveIntfCtrlData_fieldHandles, g_beNDMWSaveIntfCtrlData_fieldOffsets, base);
}

static const char *g_beNDMWSaveIntfCtrlData_messageNames[] = {
    "GENERATE",
    "LINKCOMMON",
    "ISENTRY",
    "ISRDY",
    "ONCTRL",
    "OFFCTRL",
    "SETSELECT_DATA",
};
static int g_beNDMWSaveIntfCtrlData_messageValues[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
};

igMetaEnum *beNDMWSaveIntf_GetMessageEnum(void) {
    if (g_beNDMWSaveIntfCtrlData_messageMetaEnum == 0) {
        g_beNDMWSaveIntfCtrlData_messageMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("Message", g_beNDMWSaveIntfCtrlData_messageNames, g_beNDMWSaveIntfCtrlData_messageValues, 7);
    }
    return g_beNDMWSaveIntfCtrlData_messageMetaEnum;
}

