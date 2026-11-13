igMetaObject *FUN_00195e70(void) {
    if (g_igTransformList_metaObject[0] == 0) {
        g_igTransformList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTransformList_metaObject[0];
}

igMetaObject *igTransformList_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00195f50();
    return g_igTransformList_metaObject[0];
}

int igTransformList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_0052b6f0[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_00195f50(void)
{
    igMetaObject_RunStaticInit(igTransformList_Register);
}

void igTransformList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igTransformList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igTransformList_GetMetaObject,
        igTransformList_className,
        0x14, /* instance size */
        igTransformList_GetVTable,
        0,
        0, /* extra callback item */
        g_igTransformList_callbackList /* callback list */
    );
}

void thunk_igTransformList_GetMetaObject(void) {
    igTransformList_GetMetaObject();
}

