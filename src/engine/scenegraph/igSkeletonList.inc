igMetaObject *g_igSkeletonList_metaObject;

igMetaObject *FUN_001983e0(void) {
    if (g_igSkeletonList_metaObject == 0) {
        g_igSkeletonList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igSkeletonList_metaObject;
}

igMetaObject *igSkeletonList_GetMetaObject(void)
{
    igMetaObject *g = g_igSkeletonList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSkeletonList_EnsureRegistered();
    return g_igSkeletonList_metaObject;
}

int igSkeletonList_GetVTable(void) {
    struct Obj_198480 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igSkeletonList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igSkeletonList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSkeletonList_Register);
}

static igMetaObjectCallback g_igSkeletonList_callbackList[] = { igSkeleton_EnsureRegistered, 0 };

CallbackArray *igSkeletonList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSkeletonList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igSkeletonList_GetMetaObject,
        "igSkeletonList",
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

