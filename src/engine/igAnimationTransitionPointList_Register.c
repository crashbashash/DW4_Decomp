extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationTransitionPointList_GetVTable[];
extern char thunk_igAnimationTransitionPointList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationTransitionPointList_callbackList[];
extern char igAnimationTransitionPointList_className[];
extern char g_igAnimationTransitionPointList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationTransitionPointList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationTransitionPointList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationTransitionPointList_GetMetaObject,
        igAnimationTransitionPointList_className,
        0x14, /* instance size */
        igAnimationTransitionPointList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationTransitionPointList_callbackList /* callback list */
    );
}
