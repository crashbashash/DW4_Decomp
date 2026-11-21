igMetaObject *g_beNDMWSaveCtrlCtrlData_metaObject;
int g_beNDMWSaveCtrlCtrlData_nameExternalEnumStorage;
igMetaField *g_beNDMWSaveCtrlCtrlData_orderMetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_tgPlayerMetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_isSelectMetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_st0MetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_st1MetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_st2MetaField;
igMetaField *g_beNDMWSaveCtrlCtrlData_st3MetaField;
igMetaEnum *g_beNDMWSaveCtrlCtrlData_messageMetaEnum;

beNDMWSaveCtrlCtrlData *beNDMWSaveCtrlCtrlData_Create(int allocator) {
    beNDMWSaveCtrlCtrlData_EnsureRegistered();
    return (beNDMWSaveCtrlCtrlData *)igMetaObject_CreateInstance(g_beNDMWSaveCtrlCtrlData_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWSaveCtrlCtrlData_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWSaveCtrlCtrlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWSaveCtrlCtrlData_EnsureRegistered();
    }
    return g_beNDMWSaveCtrlCtrlData_metaObject;
}

int beNDMWSaveCtrlCtrlData_GetVTable(void) {
    beNDMWSaveCtrlCtrlData obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWSaveCtrlCtrlData_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWSaveCtrlCtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveCtrlCtrlData_Register);
}

CallbackArray *beNDMWSaveCtrlCtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveCtrlCtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWSaveCtrlCtrlData_GetMetaObjectFunction,
        "beNDMWSaveCtrlCtrlData",
        0x2c, /* instance size */
        beNDMWSaveCtrlCtrlData_GetVTable,
        beNDMWSaveCtrlCtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWSaveCtrlCtrlData_GetMetaObjectFunction(void)
{
    beNDMWSaveCtrlCtrlData_GetMetaObject();
}

static FieldFactory g_beNDMWSaveCtrlCtrlData_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWSaveCtrlCtrlData_fieldTable[] = {
    "_order",
    "_tgPlayer",
    "_isSelect",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWSaveCtrlCtrlData_fieldHandles[] = {
    &g_beNDMWSaveCtrlCtrlData_orderMetaField,
    &g_beNDMWSaveCtrlCtrlData_tgPlayerMetaField,
    &g_beNDMWSaveCtrlCtrlData_isSelectMetaField,
    &g_beNDMWSaveCtrlCtrlData_st0MetaField,
    &g_beNDMWSaveCtrlCtrlData_st1MetaField,
    &g_beNDMWSaveCtrlCtrlData_st2MetaField,
    &g_beNDMWSaveCtrlCtrlData_st3MetaField,
};
static int g_beNDMWSaveCtrlCtrlData_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
};

void beNDMWSaveCtrlCtrlData_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWSaveCtrlCtrlData_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWSaveCtrlCtrlData_ctorTable, 7);
    inheritedName = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    ((Gap::Core::igStringMetaField *)nameField)->setDefault("CTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWSaveCtrlCtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, nameIndex, (igMetaField *)nameField);
    nameField->release();
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWSaveCtrlCtrlData_fieldTable, g_beNDMWSaveCtrlCtrlData_fieldHandles, g_beNDMWSaveCtrlCtrlData_fieldOffsets, base);
}

static const char *g_beNDMWSaveCtrlCtrlData_messageNames[] = {
    "GENERATE",
    "GENERATE_PS",
    "CLOSE_WIN",
    "GETCOMMON",
};
static int g_beNDMWSaveCtrlCtrlData_messageValues[] = {
    0,
    1,
    2,
    3,
};

igMetaEnum *SaveCtrlMessage_GetMetaEnum(void) {
    if (g_beNDMWSaveCtrlCtrlData_messageMetaEnum == 0) {
        g_beNDMWSaveCtrlCtrlData_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWSaveCtrlCtrlData_messageNames, g_beNDMWSaveCtrlCtrlData_messageValues, 4);
    }
    return g_beNDMWSaveCtrlCtrlData_messageMetaEnum;
}

