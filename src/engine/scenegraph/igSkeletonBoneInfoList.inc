igMetaObject *g_igSkeletonBoneInfoList_metaObject;

igMetaObject *FUN_001987f0(void) {
    if (g_igSkeletonBoneInfoList_metaObject == 0) {
        g_igSkeletonBoneInfoList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igSkeletonBoneInfoList_metaObject;
}

igMetaObject *igSkeletonBoneInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igSkeletonBoneInfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSkeletonBoneInfoList_EnsureRegistered();
    return g_igSkeletonBoneInfoList_metaObject;
}

int igSkeletonBoneInfoList_GetVTable(void) {
    struct Obj_198890 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igSkeletonBoneInfoList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igSkeletonBoneInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSkeletonBoneInfoList_Register);
}

static igMetaObjectCallback g_igSkeletonBoneInfoList_callbackList[] = { igSkeletonBoneInfo_EnsureRegistered, 0 };

CallbackArray *igSkeletonBoneInfoList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSkeletonBoneInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igSkeletonBoneInfoList_GetMetaObject,
        "igSkeletonBoneInfoList",
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

