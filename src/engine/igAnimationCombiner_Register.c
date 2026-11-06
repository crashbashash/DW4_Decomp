extern char igAnimationSystem_Register[];
extern char igAnimationCombiner_GetVTable[];
void thunk_FUN_001a8520(void);
extern char igAnimationSystem_GetPublishedMetaObject[];
extern char g_igAnimationCombiner_callbackList[];
extern char igAnimationCombiner_className[];
extern char g_igAnimationCombiner_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int thunk_FUN_001abca0[4];
int igAnimationCombiner_InitFields();

void igAnimationCombiner_Register(void) {
    SceneGraphLibrary_MarkRegistered();  /* Shared set-once latch run before every registration of this family. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationCombiner_metaObject,
        igAnimationSystem_Register,
        igAnimationSystem_GetPublishedMetaObject,
        thunk_FUN_001a8520,
        igAnimationCombiner_className,
        0x60, /* instance size */
        igAnimationCombiner_GetVTable,
        &igAnimationCombiner_InitFields,
        thunk_FUN_001abca0,                                /* static-initializer callback item (appended on fresh configuration) */
        g_igAnimationCombiner_callbackList        /* 0-terminated dependency-callback list */
    );
}
