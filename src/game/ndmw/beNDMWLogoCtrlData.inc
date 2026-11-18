igMetaObject *g_beNDMWLogoCtrlData_metaObject;
int g_beNDMWLogoCtrlData_nameExternalEnumStorage;
igMetaField *g_beNDMWLogoCtrlData_st0MetaField;
igMetaField *g_beNDMWLogoCtrlData_st1MetaField;
igMetaField *g_beNDMWLogoCtrlData_st2MetaField;
igMetaField *g_beNDMWLogoCtrlData_st3MetaField;
igMetaEnum *g_beNDMWLogoCtrlData_messageMetaEnum;

beNDMWLogoCtrlData *beNDMWLogoCtrlData_Create(int allocator) {
    beNDMWLogoCtrlData_EnsureRegistered();
    return (beNDMWLogoCtrlData *)igMetaObject_CreateInstance(g_beNDMWLogoCtrlData_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWLogoCtrlData_GetReadyMetaObject(void) {
    unsigned char b;
    if (g_beNDMWLogoCtrlData_metaObject != 0) {
        b = (g_beNDMWLogoCtrlData_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWLogoCtrlData_EnsureRegistered();
done:
    return g_beNDMWLogoCtrlData_metaObject;
}

int beNDMWLogoCtrlData_GetVTable(void) {
    beNDMWLogoCtrlData obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWLogoCtrlData_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWLogoCtrlData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLogoCtrlData_Register);
}

CallbackArray *beNDMWLogoCtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLogoCtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLogoCtrlData_GetMetaObject,
        "beNDMWLogoCtrlData",
        0x20, /* instance size */
        beNDMWLogoCtrlData_GetVTable,
        beNDMWLogoCtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWLogoCtrlData_GetMetaObject(void)
{
    beNDMWLogoCtrlData_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLogoCtrlData_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLogoCtrlData_fieldTable[] = {
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWLogoCtrlData_fieldHandles[] = {
    &g_beNDMWLogoCtrlData_st0MetaField,
    &g_beNDMWLogoCtrlData_st1MetaField,
    &g_beNDMWLogoCtrlData_st2MetaField,
    &g_beNDMWLogoCtrlData_st3MetaField,
};
static int g_beNDMWLogoCtrlData_fieldOffsets[] = {
    16,
    20,
    24,
    28,
};

void beNDMWLogoCtrlData_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWLogoCtrlData_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLogoCtrlData_ctorTable, 4);
    inheritedName = (void **)(igMetaObject_FindFieldByName((igMetaObject *)meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)((char *)((igMetaObject *)meta)->_metaFields), (int)inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    igStringMetaField_SetDefaultText((igMetaField *)nameField, "CTRL");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLogoCtrlData_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField((igMetaObject *)meta, nameIndex, (igMetaField *)nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLogoCtrlData_fieldTable, g_beNDMWLogoCtrlData_fieldHandles, g_beNDMWLogoCtrlData_fieldOffsets, base);
}

static const char *g_beNDMWLogoCtrlData_messageNames[] = {
    "RUN",
};
static int g_beNDMWLogoCtrlData_messageValues[] = {
    0,
};

igMetaEnum *beNDMWLogoCtrlData_GetMessageEnum(void) {
    if (g_beNDMWLogoCtrlData_messageMetaEnum == 0) {
        g_beNDMWLogoCtrlData_messageMetaEnum = igMetaEnum_Create("Message", g_beNDMWLogoCtrlData_messageNames, g_beNDMWLogoCtrlData_messageValues, 1);
    }
    return g_beNDMWLogoCtrlData_messageMetaEnum;
}

