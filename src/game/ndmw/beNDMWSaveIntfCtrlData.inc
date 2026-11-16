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

void beNDMWSaveIntfCtrlData_Create(int allocator) {
    beNDMWSaveIntfCtrlData_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWSaveIntfCtrlData_metaObject, allocator);
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
    union U_3bc9d0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beNDMWSaveIntfCtrlData_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void beNDMWSaveIntfCtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntfCtrlData_Register);
}

void *beNDMWSaveIntfCtrlData_Register(void) {
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
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWSaveIntfCtrlData_ctorTable, 0xF);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, inheritedName);
    nameField = (igStringMetaField *)(((DW4VC_84_1 *)(inheritedName))->vX((int)(1)));
    igStringMetaField_SetDefaultText(nameField, "CTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWSaveIntfCtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
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
        g_beNDMWSaveIntfCtrlData_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWSaveIntfCtrlData_messageNames, g_beNDMWSaveIntfCtrlData_messageValues, 7);
    }
    return g_beNDMWSaveIntfCtrlData_messageMetaEnum;
}

