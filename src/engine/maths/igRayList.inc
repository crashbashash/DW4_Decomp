igMetaObject *g_igRayList_metaObject;

igMetaObject *igRayList_GetOrCreateMetaObject(void) {
    if (g_igRayList_metaObject == 0) {
        g_igRayList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igRayList_metaObject;
}

igMetaObject *igRayList_GetMetaObject(void)
{
    igMetaObject *g = g_igRayList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRayList_EnsureRegistered();
    return g_igRayList_metaObject;
}

int igRayList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igRayList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igRayList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRayList_Register);
}

static igMetaObjectCallback g_igRayList_callbackList[] = { FUN_00188340, 0 };

void igRayList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRayList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igRayList_GetMetaObject,
        "igRayList",
        0x14, /* instance size */
        igRayList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRayList_callbackList /* callback list */
    );
}

void thunk_igRayList_GetMetaObject(void) {
    igRayList_GetMetaObject();
}

