extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationTrackList_GetVTable[];
extern char thunk_igAnimationTrackList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationTrackList_callbackList[];
extern char igAnimationTrackList_className[];
extern char g_igAnimationTrackList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationTrackList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationTrackList_metaObject,
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
