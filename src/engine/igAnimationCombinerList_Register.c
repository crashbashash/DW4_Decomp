extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationCombinerList_GetVTable[];
extern char thunk_igAnimationCombinerList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationCombinerList_callbackList[];
extern char igAnimationCombinerList_className[];
extern char g_igAnimationCombinerList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationCombinerList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationCombinerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationCombinerList_GetMetaObject,
        igAnimationCombinerList_className,
        0x14, /* instance size */
        igAnimationCombinerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationCombinerList_callbackList /* callback list */
    );
}
