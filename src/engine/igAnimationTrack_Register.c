extern char igNamedObject_GetPublishedMetaObject[];
extern char igAnimationTrack_GetVTable[];
extern char thunk_igAnimationTrack_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igAnimationTrack_callbackList[];
extern char igAnimationTrack_className[];
extern char g_igAnimationTrack_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationTrack_InitFields();

void igAnimationTrack_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationTrack_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAnimationTrack_GetMetaObject,
        igAnimationTrack_className,
        0x2C, /* instance size */
        igAnimationTrack_GetVTable,
        &igAnimationTrack_InitFields,
        0, /* extra callback item */
        g_igAnimationTrack_callbackList /* callback list */
    );
}
