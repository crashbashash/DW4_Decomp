igMetaObject *g_beLuaDataList_metaObject;

igMetaObject *beLuaDataList_GetOrCreateMetaObject(void) {
    if (g_beLuaDataList_metaObject == 0) {
        g_beLuaDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beLuaDataList_metaObject;
}

igMetaObject *beLuaDataList_GetMetaObject(void) {
    igMetaObject *g = g_beLuaDataList_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beLuaDataList_EnsureRegistered();
    return g_beLuaDataList_metaObject;
}

int beLuaDataList_GetVTable(void) {
    Obj_35b060 o;

    igObject_InitHeader(&o);
    o.vt = &g_beLuaDataList_vtable[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beLuaDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLuaDataList_Register);
}

static igMetaObjectCallback g_beLuaDataList_callbackList[] = { beLuaData_EnsureRegistered, 0 };

void *beLuaDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLuaDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLuaDataList_GetMetaObjectFunction,
        "beLuaDataList",
        0x14, /* instance size */
        beLuaDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beLuaDataList_callbackList /* callback list */
    );
}

void beLuaDataList_GetMetaObjectFunction(void)
{
    beLuaDataList_GetMetaObject();
}

