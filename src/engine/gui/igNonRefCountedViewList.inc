int FUN_0044b880(void) {
    if (DAT_0058c1b0[0] == 0) {
        DAT_0058c1b0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c1b0[0];
}

igMetaObject *igNonRefCountedViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedViewList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedViewList_EnsureRegistered();
    return g_igNonRefCountedViewList_metaObject[0];
}

int igNonRefCountedViewList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541f70[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igNonRefCountedViewList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedViewList_Register);
}

void igNonRefCountedViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedViewList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedViewList_GetMetaObject,
        igNonRefCountedViewList_className,
        0x14, /* instance size */
        igNonRefCountedViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedViewList_callbackList /* callback list */
    );
}

void thunk_igNonRefCountedViewList_GetMetaObject(void) {
    igNonRefCountedViewList_GetMetaObject();
}

