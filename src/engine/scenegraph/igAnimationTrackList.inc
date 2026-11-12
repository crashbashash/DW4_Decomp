igMetaObject *FUN_001a9d90(void) {
    if (g_igAnimationTrackList_metaObject[0] == 0) {
        g_igAnimationTrackList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAnimationTrackList_metaObject[0];
}

igMetaObject *igAnimationTrackList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTrackList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9e70();
    return g_igAnimationTrackList_metaObject[0];
}

int igAnimationTrackList_GetVTable(void) {
    struct Obj_1a9e30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00529890[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001a9e70(void)
{
    igMetaObject_RunStaticInit(igAnimationTrackList_Register);
}

void igAnimationTrackList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationTrackList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationTrackList_GetMetaObject,
        igAnimationTrackList_className,
        0x14, /* instance size */
        igAnimationTrackList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationTrackList_callbackList /* callback list */
    );
}

void thunk_igAnimationTrackList_GetMetaObject(void) {
    igAnimationTrackList_GetMetaObject();
}

