igMetaObject *g_beNDMWLoadCtrl2CtrlData_metaObject;
int g_beNDMWLoadCtrl2CtrlData_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadCtrl2CtrlData_isTitleMetaField;
igMetaField *g_beNDMWLoadCtrl2CtrlData_st0MetaField;
igMetaField *g_beNDMWLoadCtrl2CtrlData_st1MetaField;
igMetaField *g_beNDMWLoadCtrl2CtrlData_st2MetaField;
igMetaField *g_beNDMWLoadCtrl2CtrlData_st3MetaField;
igMetaEnum *g_beNDMWLoadCtrl2CtrlData_messageMetaEnum;

void beNDMWLoadCtrl2CtrlData_Create(int allocator) {
    beNDMWLoadCtrl2CtrlData_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadCtrl2CtrlData_metaObject, allocator);
}

void *beNDMWLoadCtrl2CtrlData_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadCtrl2CtrlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLoadCtrl2CtrlData_EnsureRegistered();
    }
    return g_beNDMWLoadCtrl2CtrlData_metaObject;
}

int beNDMWLoadCtrl2CtrlData_GetVTable(void) {
    beNDMWLoadCtrl2CtrlData obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWLoadCtrl2CtrlData_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWLoadCtrl2CtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2CtrlData_Register);
}

void *beNDMWLoadCtrl2CtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadCtrl2CtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadCtrl2CtrlData_GetMetaObject,
        "beNDMWLoadCtrl2CtrlData",
        0x24, /* instance size */
        beNDMWLoadCtrl2CtrlData_GetVTable,
        beNDMWLoadCtrl2CtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLoadCtrl2CtrlData_GetMetaObject(void)
{
    beNDMWLoadCtrl2CtrlData_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadCtrl2CtrlData_ctorTable[] = {
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadCtrl2CtrlData_fieldTable[] = {
    "_isTitle",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLoadCtrl2CtrlData_fieldHandles[] = {
    &g_beNDMWLoadCtrl2CtrlData_isTitleMetaField,
    &g_beNDMWLoadCtrl2CtrlData_st0MetaField,
    &g_beNDMWLoadCtrl2CtrlData_st1MetaField,
    &g_beNDMWLoadCtrl2CtrlData_st2MetaField,
    &g_beNDMWLoadCtrl2CtrlData_st3MetaField,
};
static int g_beNDMWLoadCtrl2CtrlData_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
};

void beNDMWLoadCtrl2CtrlData_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWLoadCtrl2CtrlData_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadCtrl2CtrlData_ctorTable, 5);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    igStringMetaField_SetDefaultText(nameField, "CTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadCtrl2CtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    igBoolMetaField_SetDefaultValue(((int)igMetaObject_GetFieldAt(meta, base)), 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadCtrl2CtrlData_fieldTable, g_beNDMWLoadCtrl2CtrlData_fieldHandles, g_beNDMWLoadCtrl2CtrlData_fieldOffsets, base);
}

static const char *g_beNDMWLoadCtrl2CtrlData_messageNames[] = {
    "GENERATE",
    "GENERATE_TITLE",
    "CLOSE_WIN",
    "GETCOMMON",
};
static int g_beNDMWLoadCtrl2CtrlData_messageValues[] = {
    0,
    1,
    2,
    3,
};

igMetaEnum *LoadCtrl2Message_GetMetaEnum(void) {
    if (g_beNDMWLoadCtrl2CtrlData_messageMetaEnum == 0) {
        g_beNDMWLoadCtrl2CtrlData_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWLoadCtrl2CtrlData_messageNames, g_beNDMWLoadCtrl2CtrlData_messageValues, 4);
    }
    return g_beNDMWLoadCtrl2CtrlData_messageMetaEnum;
}

