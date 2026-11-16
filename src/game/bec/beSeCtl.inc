igMetaObject *g_beSeCtl_metaObject;
igMetaField *g_beSeCtl_sndMngMetaField;

void beSeCtl_CreateInstance(int allocator) {
    beSeCtl_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x587FE8, allocator);
}

igMetaObject *beSeCtl_GetOrCreateMetaObject(void) {
    if (g_beSeCtl_metaObject == 0) {
        g_beSeCtl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSeCtl_metaObject;
}

igMetaObject *beSeCtl_GetMetaObject(void) {
    igMetaObject *g = g_beSeCtl_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beSeCtl_EnsureRegistered();
done:
    return g_beSeCtl_metaObject;
}

int beSeCtl_GetVTable(void) {
    beSeCtl obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beSeCtl_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beSeCtl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSeCtl_Register);
}

static igMetaObjectCallback g_beSeCtl_callbackList[] = { beSound_EnsureRegistered, 0 };

void *beSeCtl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSeCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beSeCtl_GetMetaObjectFunction,
        "beSeCtl",
        0x24, /* instance size */
        beSeCtl_GetVTable,
        beSeCtl_InitFields,
        0, /* extra callback item */
        g_beSeCtl_callbackList /* callback list */
    );
}

void beSeCtl_GetMetaObjectFunction(void)
{
    beSeCtl_GetMetaObject();
}

static FieldFactory g_beSeCtl_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beSeCtl_fieldTable[] = {
    "_sndMng",
};
static igMetaField **g_beSeCtl_fieldHandles[] = {
    &g_beSeCtl_sndMngMetaField,
};
static int g_beSeCtl_fieldOffsets[] = {
    32,
};

void beSeCtl_InitFields(void) {
    int base;
    void *sndMng;
    void *meta;

    meta = (void *)g_beSeCtl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSeCtl_ctorTable, 1);
    sndMng = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)sndMng)->_metaObject = (int)beSound_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)sndMng)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beSeCtl_fieldTable, g_beSeCtl_fieldHandles, g_beSeCtl_fieldOffsets, base);
}

