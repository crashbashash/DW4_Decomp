igMetaObject *FUN_001987f0(void) {
    if (g_igSkeletonBoneInfoList_metaObject[0] == 0) {
        g_igSkeletonBoneInfoList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igSkeletonBoneInfoList_metaObject[0];
}

igMetaObject *igSkeletonBoneInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igSkeletonBoneInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001988d0();
    return g_igSkeletonBoneInfoList_metaObject[0];
}

int igSkeletonBoneInfoList_GetVTable(void) {
    struct Obj_198890 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b2d0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001988d0(void)
{
    igMetaObject_RunStaticInit(igSkeletonBoneInfoList_Register);
}

void igSkeletonBoneInfoList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igSkeletonBoneInfoList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igSkeletonBoneInfoList_GetMetaObject,
        igSkeletonBoneInfoList_className,
        0x14, /* instance size */
        igSkeletonBoneInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igSkeletonBoneInfoList_callbackList /* callback list */
    );
}

void thunk_igSkeletonBoneInfoList_GetMetaObject(void) {
    igSkeletonBoneInfoList_GetMetaObject();
}

