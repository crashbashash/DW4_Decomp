igMetaObject *g_igControllerList_metaObject;

igMetaObject *FUN_00146300(void) {
    if (g_igControllerList_metaObject == 0) {
        g_igControllerList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igControllerList_metaObject;
}

igMetaObject *igControllerList_GetMetaObject(void)
{
    igMetaObject *g = g_igControllerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001463e0();
    return g_igControllerList_metaObject;
}

int igControllerList_GetVTable(void) {
    Obj_1463a0 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00524f70[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001463e0(void)
{
    igMetaObject_RunStaticInit(igControllerList_Register);
}

static igMetaObjectCallback g_igControllerList_callbackList[] = { FUN_00146900, 0 };

void igControllerList_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igControllerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igControllerList_GetMetaObject,
        "igControllerList",
        0x14, /* instance size */
        igControllerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igControllerList_callbackList /* callback list */
    );
}

void thunk_igControllerList_GetMetaObject(void) {
    igControllerList_GetMetaObject();
}

