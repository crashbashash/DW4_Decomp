igMetaObject *g_bePoint01_metaObject;
igMetaField *g_bePoint01_pointNoMetaField;

bePoint01 *bePoint01_CreateInstance(int allocator) {
    bePoint01_EnsureRegistered();
    return (bePoint01 *)igMetaObject_CreateInstance(*(int *)0x588498, allocator);
}

igMetaObject *bePoint01_GetOrCreateMetaObject(void) {
    if (g_bePoint01_metaObject == 0) {
        g_bePoint01_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_bePoint01_metaObject;
}

void *bePoint01_GetMetaObject(void) {
    bool ok;
    if (g_bePoint01_metaObject == 0) goto make;
    ok = !!(g_bePoint01_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    bePoint01_EnsureRegistered();
done:;
    return g_bePoint01_metaObject;
}

int bePoint01_GetVTable(void) {
    bePoint01 obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_bePoint01_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void bePoint01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePoint01_Register);
}

void *bePoint01_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePoint01_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        bePoint01_GetMetaObjectFunction,
        "bePoint01",
        0x24, /* instance size */
        bePoint01_GetVTable,
        bePoint01_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void bePoint01_GetMetaObjectFunction(void)
{
    bePoint01_GetMetaObject();
}

static FieldFactory g_bePoint01_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_bePoint01_fieldTable[] = {
    "_pointNo",
};
static igMetaField **g_bePoint01_fieldHandles[] = {
    &g_bePoint01_pointNoMetaField,
};
static int g_bePoint01_fieldOffsets[] = {
    32,
};

void bePoint01_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_bePoint01_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_bePoint01_ctorTable, 1);
    igMetaObject_NameFields(meta, g_bePoint01_fieldTable, g_bePoint01_fieldHandles, g_bePoint01_fieldOffsets, base);
}

