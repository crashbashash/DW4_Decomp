igMetaObject *g_igWindowResizeEventReceiver_metaObject;
igMetaField *g_igWindowResizeEventReceiver_insightCoreMetaField;

igMetaObject *FUN_00233080(void) {
    if (g_igWindowResizeEventReceiver_metaObject == 0) {
        g_igWindowResizeEventReceiver_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igWindowResizeEventReceiver_metaObject;
}

igMetaObject *igWindowResizeEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igWindowResizeEventReceiver_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233160();
    return g_igWindowResizeEventReceiver_metaObject;
}

int igWindowResizeEventReceiver_GetVTable(void) {
    struct Obj_233120 o;
    igObject_InitHeader(&o);
    o.vt = &g_igWindowResizeEventReceiver_vtable[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00233160(void)
{
    igMetaObject_RunStaticInit(igWindowResizeEventReceiver_Register);
}

static igMetaObjectCallback g_igWindowResizeEventReceiver_callbackList[] = { igInsightCore_EnsureRegistered, 0 };

void igWindowResizeEventReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igWindowResizeEventReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igWindowResizeEventReceiver_GetMetaObject,
        "igWindowResizeEventReceiver",
        0xC, /* instance size */
        igWindowResizeEventReceiver_GetVTable,
        &igWindowResizeEventReceiver_InitFields,
        0, /* extra callback item */
        g_igWindowResizeEventReceiver_callbackList /* callback list */
    );
}

void thunk_igWindowResizeEventReceiver_GetMetaObject(void) {
    igWindowResizeEventReceiver_GetMetaObject();
}

int FUN_00233200(void) {
    return g_igEventReceiver_metaObject[0];
}

static FieldFactory g_igWindowResizeEventReceiver_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igWindowResizeEventReceiver_fieldTable[] = {
    "_insightCore",
};
static igMetaField **g_igWindowResizeEventReceiver_fieldHandles[] = {
    &g_igWindowResizeEventReceiver_insightCoreMetaField,
};
static int g_igWindowResizeEventReceiver_fieldOffsets[] = {
    8,
};

void igWindowResizeEventReceiver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igWindowResizeEventReceiver_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igWindowResizeEventReceiver_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, g_igWindowResizeEventReceiver_fieldTable, g_igWindowResizeEventReceiver_fieldHandles, g_igWindowResizeEventReceiver_fieldOffsets, temp_s2);
}

