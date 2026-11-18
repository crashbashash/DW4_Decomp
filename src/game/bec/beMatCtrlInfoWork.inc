igMetaObject *g_beMatCtrlInfoWork_metaObject;
igMetaField *g_beMatCtrlInfoWork_runFlagListMetaField;
igMetaField *g_beMatCtrlInfoWork_matOnPlListsMetaField;

beMatCtrlInfoWork *beMatCtrlInfoWork_Create(int allocator) {
    beMatCtrlInfoWork_EnsureRegistered();
    return (beMatCtrlInfoWork *)igMetaObject_CreateInstance(g_beMatCtrlInfoWork_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beMatCtrlInfoWork_GetOrCreateMetaObject(void) {
    if (g_beMatCtrlInfoWork_metaObject == 0) {
        g_beMatCtrlInfoWork_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beMatCtrlInfoWork_metaObject;
}

void *beMatCtrlInfoWork_GetMetaObject(void) {
    igMetaObject *g = g_beMatCtrlInfoWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMatCtrlInfoWork_EnsureRegistered();
    }
    return g_beMatCtrlInfoWork_metaObject;
}

int beMatCtrlInfoWork_GetVTable(void) {
    beMatCtrlInfoWork obj;
    int vtable;
    igObject **matOnPlListsSlot;
    igObject **runFlagListSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMatCtrlInfoWork_vtable[0];
    runFlagListSlot = (igObject **)&obj._runFlagList;
    *runFlagListSlot = 0;
    matOnPlListsSlot = (igObject **)&obj._matOnPlLists;
    *matOnPlListsSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beMatCtrlInfoWork_vtable[0];
    igObjectRef_Release(matOnPlListsSlot);
    igObjectRef_Release(runFlagListSlot);
    return vtable;
}

void beMatCtrlInfoWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrlInfoWork_Register);
}

static igMetaObjectCallback g_beMatCtrlInfoWork_callbackList[] = { igBoolList_EnsureRegistered, igIntListList_EnsureRegistered, 0 };

CallbackArray *beMatCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beMatCtrlInfoWork_GetMetaObjectFunction,
        "beMatCtrlInfoWork",
        0x10, /* instance size */
        beMatCtrlInfoWork_GetVTable,
        beMatCtrlInfoWork_InitFields,
        0, /* extra callback item */
        g_beMatCtrlInfoWork_callbackList /* callback list */
    );
}

void beMatCtrlInfoWork_GetMetaObjectFunction(void)
{
    beMatCtrlInfoWork_GetMetaObject();
}

static FieldFactory g_beMatCtrlInfoWork_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMatCtrlInfoWork_fieldTable[] = {
    "_runFlagList",
    "_matOnPlLists",
};
static igMetaField **g_beMatCtrlInfoWork_fieldHandles[] = {
    &g_beMatCtrlInfoWork_runFlagListMetaField,
    &g_beMatCtrlInfoWork_matOnPlListsMetaField,
};
static int g_beMatCtrlInfoWork_fieldOffsets[] = {
    8,
    12,
};

void beMatCtrlInfoWork_InitFields(void) {
    int base;
    void *matOnPlLists;
    void *runFlagList;
    igMetaObject *meta;

    meta = g_beMatCtrlInfoWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMatCtrlInfoWork_ctorTable, 2);
    runFlagList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)runFlagList)->_metaObject = (int)igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)runFlagList)->_construct = 1;
    matOnPlLists = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)matOnPlLists)->_metaObject = (int)igIntListList_GetOrCreateMetaObject();
    ((igRefMetaField *)matOnPlLists)->_construct = 1;
    igMetaObject_NameFields(meta, g_beMatCtrlInfoWork_fieldTable, g_beMatCtrlInfoWork_fieldHandles, g_beMatCtrlInfoWork_fieldOffsets, base);
}

