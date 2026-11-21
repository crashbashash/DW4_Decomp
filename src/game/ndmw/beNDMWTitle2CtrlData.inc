igMetaObject *g_beNDMWTitle2CtrlData_metaObject;
int g_beNDMWTitle2CtrlData_nameExternalEnumStorage;
igMetaField *g_beNDMWTitle2CtrlData_isRunMetaField;
igMetaField *g_beNDMWTitle2CtrlData_logoCountMetaField;
igMetaField *g_beNDMWTitle2CtrlData_gameMenuCntMetaField;
igMetaField *g_beNDMWTitle2CtrlData_gameMenuNextMetaField;
igMetaField *g_beNDMWTitle2CtrlData_st0MetaField;
igMetaField *g_beNDMWTitle2CtrlData_st1MetaField;
igMetaField *g_beNDMWTitle2CtrlData_st2MetaField;
igMetaField *g_beNDMWTitle2CtrlData_st3MetaField;
igMetaEnum *g_beNDMWTitle2CtrlData_messageMetaEnum;

beNDMWTitle2CtrlData *beNDMWTitle2CtrlData_Create(int allocator) {
    beNDMWTitle2CtrlData_EnsureRegistered();
    return (beNDMWTitle2CtrlData *)igMetaObject_CreateInstance(g_beNDMWTitle2CtrlData_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWTitle2CtrlData_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWTitle2CtrlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWTitle2CtrlData_EnsureRegistered();
    }
    return g_beNDMWTitle2CtrlData_metaObject;
}

int beNDMWTitle2CtrlData_GetVTable(void) {
    beNDMWTitle2CtrlData obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWTitle2CtrlData_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWTitle2CtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWTitle2CtrlData_Register);
}

CallbackArray *beNDMWTitle2CtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWTitle2CtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWTitle2CtrlData_GetMetaObjectFunction,
        "beNDMWTitle2CtrlData",
        0x30, /* instance size */
        beNDMWTitle2CtrlData_GetVTable,
        beNDMWTitle2CtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWTitle2CtrlData_GetMetaObjectFunction(void)
{
    beNDMWTitle2CtrlData_GetMetaObject();
}

static FieldFactory g_beNDMWTitle2CtrlData_ctorTable[] = {
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWTitle2CtrlData_fieldTable[] = {
    "_isRun",
    "_logoCount",
    "_gameMenuCnt",
    "_gameMenuNext",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWTitle2CtrlData_fieldHandles[] = {
    &g_beNDMWTitle2CtrlData_isRunMetaField,
    &g_beNDMWTitle2CtrlData_logoCountMetaField,
    &g_beNDMWTitle2CtrlData_gameMenuCntMetaField,
    &g_beNDMWTitle2CtrlData_gameMenuNextMetaField,
    &g_beNDMWTitle2CtrlData_st0MetaField,
    &g_beNDMWTitle2CtrlData_st1MetaField,
    &g_beNDMWTitle2CtrlData_st2MetaField,
    &g_beNDMWTitle2CtrlData_st3MetaField,
};
static int g_beNDMWTitle2CtrlData_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
};

void beNDMWTitle2CtrlData_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWTitle2CtrlData_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWTitle2CtrlData_ctorTable, 8);
    inheritedName = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    ((Gap::Core::igStringMetaField *)nameField)->setDefault("CTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWTitle2CtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, nameIndex, (igMetaField *)nameField);
    nameField->release();
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWTitle2CtrlData_fieldTable, g_beNDMWTitle2CtrlData_fieldHandles, g_beNDMWTitle2CtrlData_fieldOffsets, base);
}

static const char *g_beNDMWTitle2CtrlData_messageNames[] = {
    "RUN",
    "GAMESTART",
};
static int g_beNDMWTitle2CtrlData_messageValues[] = {
    0,
    1,
};

igMetaEnum *beNDMWTitle2CtrlData_GetMessageEnum(void) {
    if (g_beNDMWTitle2CtrlData_messageMetaEnum == 0) {
        g_beNDMWTitle2CtrlData_messageMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("Message", g_beNDMWTitle2CtrlData_messageNames, g_beNDMWTitle2CtrlData_messageValues, 2);
    }
    return g_beNDMWTitle2CtrlData_messageMetaEnum;
}

