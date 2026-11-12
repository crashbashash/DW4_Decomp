igMetaObject *FUN_00233080(void) {
    if (g_igWindowResizeEventReceiver_metaObject[0] == 0) {
        g_igWindowResizeEventReceiver_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igWindowResizeEventReceiver_metaObject[0];
}

igMetaObject *igWindowResizeEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igWindowResizeEventReceiver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233160();
    return g_igWindowResizeEventReceiver_metaObject[0];
}

int igWindowResizeEventReceiver_GetVTable(void) {
    struct Obj_233120 o;
    igObject_InitHeader(&o);
    o.vt = &DAT_0052c9f0[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00233160(void)
{
    igMetaObject_RunStaticInit(igWindowResizeEventReceiver_Register);
}

void igWindowResizeEventReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igWindowResizeEventReceiver_metaObject,
        igEventReceiver_Register,
        igEventReceiver_GetPublishedMetaObject,
        thunk_igWindowResizeEventReceiver_GetMetaObject,
        igWindowResizeEventReceiver_className,
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

void igWindowResizeEventReceiver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igWindowResizeEventReceiver_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004981f8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00232840();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00498200[0], &DAT_00498208[0], &DAT_00498210[0], temp_s2);
}

