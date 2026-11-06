extern char igNamedObject_GetPublishedMetaObject[];
extern char thunk_igAnimationSystem_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igAnimationSystem_callbackList[];
extern char igAnimationSystem_className[];
extern char g_igAnimationSystem_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationSystem_InitFields();

void igAnimationSystem_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAnimationSystem_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAnimationSystem_GetMetaObject,
        igAnimationSystem_className,
        0x10, /* instance size */
        0,
        &igAnimationSystem_InitFields,
        0, /* extra callback item */
        g_igAnimationSystem_callbackList /* callback list */
    );
}
