igMetaObject *g_beMemory_metaObject;
igMetaField *g_beMemory_messengerMetaField;
igMetaField *g_beMemory_padManagerMetaField;
igMetaField *g_beMemory_isDispMetaField;
igMetaField *g_beMemory_colorIndexMetaField;
igMetaField *g_beMemory_updateCountMetaField;

igMetaObject *beMemory_GetOrCreateMetaObject(void) {
    if (g_beMemory_metaObject == 0) {
        g_beMemory_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMemory_metaObject;
}

void *beMemory_GetMetaObject(void) {
    igMetaObject *g = g_beMemory_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMemory_EnsureRegistered();
    }
    return g_beMemory_metaObject;
}

int beMemory_GetVTable(void) {
    beMemory obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beMemory_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beMemory_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMemory_Register);
}

static igMetaObjectCallback g_beMemory_callbackList[] = { beMessenger_EnsureRegistered, bePadManager_EnsureRegistered, 0 };

void *beMemory_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMemory_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beMemory_GetMetaObjectFunction,
        "beMemory",
        0x24, /* instance size */
        beMemory_GetVTable,
        beMemory_InitFields,
        0, /* extra callback item */
        g_beMemory_callbackList /* callback list */
    );
}

void beMemory_GetMetaObjectFunction(void)
{
    beMemory_GetMetaObject();
}

static FieldFactory g_beMemory_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beMemory_fieldTable[] = {
    "_messenger",
    "_padManager",
    "_isDisp",
    "_colorIndex",
    "_updateCount",
};
static igMetaField **g_beMemory_fieldHandles[] = {
    &g_beMemory_messengerMetaField,
    &g_beMemory_padManagerMetaField,
    &g_beMemory_isDispMetaField,
    &g_beMemory_colorIndexMetaField,
    &g_beMemory_updateCountMetaField,
};
static int g_beMemory_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
};

void beMemory_InitFields(void) {
    int base;
    void *padManager;
    void *messenger;
    void *meta;

    meta = (void *)g_beMemory_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMemory_ctorTable, 5);
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)padManager)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beMemory_fieldTable, g_beMemory_fieldHandles, g_beMemory_fieldOffsets, base);
}

