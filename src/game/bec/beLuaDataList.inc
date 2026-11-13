igMetaObject *FUN_0035afc0(void) {
    if (g_beLuaDataList_metaObject[0] == 0) {
        g_beLuaDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beLuaDataList_metaObject[0];
}

igMetaObject *FUN_0035b010(void) {
    igMetaObject *g = g_beLuaDataList_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_0035b0a0();
    return g_beLuaDataList_metaObject[0];
}

int beLuaDataList_GetVTable(void) {
    Obj_35b060 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_005368f0[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0035b0a0(void)
{
    igMetaObject_RunStaticInit(beLuaDataList_Register);
}

void *beLuaDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLuaDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLuaDataList_GetMetaObject,
        beLuaDataList_className,
        0x14, /* instance size */
        beLuaDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beLuaDataList_callbackList /* callback list */
    );
}

void beLuaDataList_GetMetaObject(void)
{
    FUN_0035b010();
}

