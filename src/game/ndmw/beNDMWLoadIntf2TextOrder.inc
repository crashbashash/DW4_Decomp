igMetaObject *g_beNDMWLoadIntf2TextOrder_metaObject;
int g_beNDMWLoadIntf2TextOrder_nameExternalEnumStorage;
igMetaField *g_beNDMWLoadIntf2TextOrder_messengerMetaField;
igMetaField *g_beNDMWLoadIntf2TextOrder_luaMetaField;

void beNDMWLoadIntf2TextOrder_Create(int allocator) {
    beNDMWLoadIntf2TextOrder_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2TextOrder_metaObject, allocator);
}

igMetaObject *beNDMWLoadIntf2TextOrder_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadIntf2TextOrder_metaObject == 0) {
        g_beNDMWLoadIntf2TextOrder_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadIntf2TextOrder_metaObject;
}

void *beNDMWLoadIntf2TextOrder_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2TextOrder_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLoadIntf2TextOrder_EnsureRegistered();
    }
    return g_beNDMWLoadIntf2TextOrder_metaObject;
}

int beNDMWLoadIntf2TextOrder_GetVTable(void) {
    beNDMWLoadIntf2TextOrder obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2TextOrder_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWLoadIntf2TextOrder_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2TextOrder_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2TextOrder_callbackList[] = { beMessenger_EnsureRegistered, beLua_EnsureRegistered, 0 };

void *beNDMWLoadIntf2TextOrder_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2TextOrder_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2TextOrder_GetMetaObject,
        "beNDMWLoadIntf2TextOrder",
        0x18, /* instance size */
        beNDMWLoadIntf2TextOrder_GetVTable,
        beNDMWLoadIntf2TextOrder_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2TextOrder_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2TextOrder_GetMetaObject(void)
{
    beNDMWLoadIntf2TextOrder_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2TextOrder_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWLoadIntf2TextOrder_fieldTable[] = {
    "_messenger",
    "_lua",
};
static igMetaField **g_beNDMWLoadIntf2TextOrder_fieldHandles[] = {
    &g_beNDMWLoadIntf2TextOrder_messengerMetaField,
    &g_beNDMWLoadIntf2TextOrder_luaMetaField,
};
static int g_beNDMWLoadIntf2TextOrder_fieldOffsets[] = {
    16,
    20,
};

void beNDMWLoadIntf2TextOrder_InitFields(void) {
    int base;
    int nameIndex;
    void **inheritedName;
    void *messenger;
    void *lua;
    void *meta;
    igStringMetaField *nameField;

    /* matching construct: variant search - the handle stays a void * (typed igMetaObject * swaps s0/s1) */

    meta = (void *)(g_beNDMWLoadIntf2TextOrder_metaObject);
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_beNDMWLoadIntf2TextOrder_ctorTable, 2);
    inheritedName = (void **)(igMetaObject_FindFieldByName(meta, "_name"));
    nameIndex = ObjectPointerList_FindIndex(((igMetaObject *)meta)->_metaFields, inheritedName);
    nameField = (igStringMetaField *)((igObjectDispatchView *)inheritedName)->CloneViaMetadata(1);
    igStringMetaField_SetDefaultText(nameField, "TEXTORDER");
    nameField->_externalEnumStorage = (int)(&g_beNDMWLoadIntf2TextOrder_nameExternalEnumStorage);
    igMetaObject_FinalizeAndReplaceField(meta, nameIndex, nameField);
    nameField->_refCount = nameField->_refCount - 1;
    if (((unsigned long long)(long long)nameField->_refCount & 0x7fffffULL) == 0) {
        igObject_Destroy(nameField);
    }
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    lua = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)lua)->_metaObject = beLua_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)lua)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_beNDMWLoadIntf2TextOrder_fieldTable, g_beNDMWLoadIntf2TextOrder_fieldHandles, g_beNDMWLoadIntf2TextOrder_fieldOffsets, base);
}

