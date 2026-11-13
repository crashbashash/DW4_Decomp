igMetaObject *FUN_00195d00(void) {
    if (g_igNonRefCountedTransformList_metaObject[0] == 0) {
        g_igNonRefCountedTransformList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igNonRefCountedTransformList_metaObject[0];
}

igMetaObject *igNonRefCountedTransformList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedTransformList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00195de0();
    return g_igNonRefCountedTransformList_metaObject[0];
}

int igNonRefCountedTransformList_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052b760[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_00195de0(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedTransformList_Register);
}

void igNonRefCountedTransformList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNonRefCountedTransformList_metaObject),
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedTransformList_GetMetaObject,
        igNonRefCountedTransformList_className,
        0x14, /* instance size */
        igNonRefCountedTransformList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedTransformList_callbackList /* callback list */
    );
}

void thunk_igNonRefCountedTransformList_GetMetaObject(void) {
    igNonRefCountedTransformList_GetMetaObject();
}

