igMetaObject *g_igAnimationTrackList_metaObject;

igMetaObject *FUN_001a9d90(void) {
    if (g_igAnimationTrackList_metaObject == 0) {
        g_igAnimationTrackList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAnimationTrackList_metaObject;
}

igMetaObject *igAnimationTrackList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTrackList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationTrackList_EnsureRegistered();
    return g_igAnimationTrackList_metaObject;
}

int igAnimationTrackList_GetVTable(void) {
    struct Obj_1a9e30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igAnimationTrackList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igAnimationTrackList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationTrackList_Register);
}

static igMetaObjectCallback g_igAnimationTrackList_callbackList[] = { igAnimationTrack_EnsureRegistered, 0 };

void igAnimationTrackList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationTrackList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationTrackList_GetMetaObject,
        "igAnimationTrackList",
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

