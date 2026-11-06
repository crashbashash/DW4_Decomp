extern char igInfo_GetPublishedMetaObject[];
extern char igAnimationDatabase_GetVTable[];
extern char thunk_igAnimationDatabase_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igAnimationDatabase_callbackList[];
extern char igAnimationDatabase_className[];
extern char g_igAnimationDatabase_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationDatabase_InitFields();

void igAnimationDatabase_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationDatabase_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igAnimationDatabase_GetMetaObject,
        igAnimationDatabase_className,
        0x28, /* instance size */
        igAnimationDatabase_GetVTable,
        &igAnimationDatabase_InitFields,
        0, /* extra callback item */
        g_igAnimationDatabase_callbackList /* callback list */
    );
}
