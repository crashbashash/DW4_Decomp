int FUN_001983e0(void) {
    if (DAT_005614a8[0] == 0) {
        DAT_005614a8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005614a8[0];
}

igMetaObject *igSkeletonList_GetMetaObject(void)
{
    igMetaObject *g = g_igSkeletonList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001984c0();
    return g_igSkeletonList_metaObject[0];
}

int igSkeletonList_GetVTable(void) {
    struct Obj_198480 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b340[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001984c0(void)
{
    igMetaObject_RunStaticInit(igSkeletonList_Register);
}

void igSkeletonList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igSkeletonList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igSkeletonList_GetMetaObject,
        igSkeletonList_className,
        0x14, /* instance size */
        igSkeletonList_GetVTable,
        0,
        0, /* extra callback item */
        g_igSkeletonList_callbackList /* callback list */
    );
}

void thunk_igSkeletonList_GetMetaObject(void) {
    igSkeletonList_GetMetaObject();
}

