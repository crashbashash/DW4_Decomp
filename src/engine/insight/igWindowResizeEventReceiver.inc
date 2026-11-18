igMetaObject *g_igWindowResizeEventReceiver_metaObject;
igMetaField *g_igWindowResizeEventReceiver_insightCoreMetaField;

igMetaObject *igWindowResizeEventReceiver_GetOrCreateMetaObject(void) {
    if (g_igWindowResizeEventReceiver_metaObject == 0) {
        g_igWindowResizeEventReceiver_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igWindowResizeEventReceiver_metaObject;
}

igMetaObject *igWindowResizeEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igWindowResizeEventReceiver_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igWindowResizeEventReceiver_EnsureRegistered();
    return g_igWindowResizeEventReceiver_metaObject;
}

int igWindowResizeEventReceiver_GetVTable(void) {
    struct Obj_233120 o;
    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igWindowResizeEventReceiver_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igWindowResizeEventReceiver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igWindowResizeEventReceiver_Register);
}

static igMetaObjectCallback g_igWindowResizeEventReceiver_callbackList[] = { igInsightCore_EnsureRegistered, 0 };

CallbackArray *igWindowResizeEventReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igWindowResizeEventReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        igWindowResizeEventReceiver_GetMetaObjectFunction,
        "igWindowResizeEventReceiver",
        0xC, /* instance size */
        igWindowResizeEventReceiver_GetVTable,
        &igWindowResizeEventReceiver_InitFields,
        0, /* extra callback item */
        g_igWindowResizeEventReceiver_callbackList /* callback list */
    );
}

void igWindowResizeEventReceiver_GetMetaObjectFunction(void) {
    igWindowResizeEventReceiver_GetMetaObject();
}

igMetaObject *igEventReceiver_GetPublishedMetaObject(void) {
    return g_igEventReceiver_metaObject;
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
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igWindowResizeEventReceiver_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igWindowResizeEventReceiver_fieldTable, g_igWindowResizeEventReceiver_fieldHandles, g_igWindowResizeEventReceiver_fieldOffsets, temp_s2);
}

