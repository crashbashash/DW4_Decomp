igMetaObject *g_igInfoManagerList_metaObject;

igMetaObject *FUN_00233750(void) {
    if (g_igInfoManagerList_metaObject == 0) {
        g_igInfoManagerList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igInfoManagerList_metaObject;
}

igMetaObject *igInfoManagerList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManagerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233830();
    return g_igInfoManagerList_metaObject;
}

int igInfoManagerList_GetVTable(void) {
    struct Obj_2337f0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igInfoManagerList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_00233830(void)
{
    igMetaObject_RunStaticInit(igInfoManagerList_Register);
}

static igMetaObjectCallback g_igInfoManagerList_callbackList[] = { FUN_00233910, 0 };

CallbackArray *igInfoManagerList_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igInfoManagerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igInfoManagerList_GetMetaObject,
        "igInfoManagerList",
        0x14, /* instance size */
        igInfoManagerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInfoManagerList_callbackList /* callback list */
    );
}

void thunk_igInfoManagerList_GetMetaObject(void) {
    igInfoManagerList_GetMetaObject();
}

