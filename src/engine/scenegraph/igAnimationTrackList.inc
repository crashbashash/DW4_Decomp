int FUN_001a9d90(void) {
    if (DAT_00562428[0] == 0) {
        DAT_00562428[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562428[0];
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
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
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

