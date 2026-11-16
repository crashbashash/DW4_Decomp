igMetaObject *g_beChangePosTransform_metaObject;
igMetaField *g_beChangePosTransform_oldPosMetaField;

void beChangePosTransform_CreateInstance(int allocator) {
    beChangePosTransform_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589B80, allocator);
}

igMetaObject *beChangePosTransform_GetOrCreateMetaObject(void) {
    if (g_beChangePosTransform_metaObject == 0) {
        g_beChangePosTransform_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beChangePosTransform_metaObject;
}

igMetaObject *beChangePosTransform_GetMetaObject(void) {
    if (g_beChangePosTransform_metaObject == 0 || !isValid(g_beChangePosTransform_metaObject)) beChangePosTransform_EnsureRegistered();
    return g_beChangePosTransform_metaObject;
}

int beChangePosTransform_GetVTable(void) {
    beChangePosTransform obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beChangePosTransform_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beChangePosTransform_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beChangePosTransform_Register);
}

void *beChangePosTransform_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beChangePosTransform_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beChangePosTransform_GetMetaObjectFunction,
        "beChangePosTransform",
        0x2c, /* instance size */
        beChangePosTransform_GetVTable,
        beChangePosTransform_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beChangePosTransform_GetMetaObjectFunction(void)
{
    beChangePosTransform_GetMetaObject();
}

static FieldFactory g_beChangePosTransform_ctorTable[] = {
    igVec3fMetaField_CreateInstance,
};
static const char *g_beChangePosTransform_fieldTable[] = {
    "_oldPos",
};
static igMetaField **g_beChangePosTransform_fieldHandles[] = {
    &g_beChangePosTransform_oldPosMetaField,
};
static int g_beChangePosTransform_fieldOffsets[] = {
    32,
};

void beChangePosTransform_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beChangePosTransform_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beChangePosTransform_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beChangePosTransform_fieldTable, g_beChangePosTransform_fieldHandles, g_beChangePosTransform_fieldOffsets, base);
}

