igMetaObject *FUN_00451950(void) {
    if (g_igDefaultAspectElementList_metaObject[0] == 0) {
        g_igDefaultAspectElementList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igDefaultAspectElementList_metaObject[0];
}

igMetaObject *igDefaultAspectElementList_GetMetaObject(void)
{
    igMetaObject *g = g_igDefaultAspectElementList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDefaultAspectElementList_EnsureRegistered();
    return g_igDefaultAspectElementList_metaObject[0];
}

int igDefaultAspectElementList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005418a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igDefaultAspectElementList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDefaultAspectElementList_Register);
}

void igDefaultAspectElementList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultAspectElementList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igDefaultAspectElementList_GetMetaObject,
        igDefaultAspectElementList_className,
        0x14, /* instance size */
        igDefaultAspectElementList_GetVTable,
        0,
        0, /* extra callback item */
        g_igDefaultAspectElementList_callbackList /* callback list */
    );
}

void thunk_igDefaultAspectElementList_GetMetaObject(void) {
    igDefaultAspectElementList_GetMetaObject();
}

