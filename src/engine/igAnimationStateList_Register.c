extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationStateList_GetVTable[];
extern char thunk_igAnimationStateList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationStateList_callbackList[];
extern char igAnimationStateList_className[];
extern char g_igAnimationStateList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationStateList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationStateList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationStateList_GetMetaObject,
        igAnimationStateList_className,
        0x14, /* instance size */
        igAnimationStateList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationStateList_callbackList /* callback list */
    );
}
