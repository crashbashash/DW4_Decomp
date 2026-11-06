extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationTransitionDefinitionList_GetVTable[];
extern char thunk_igAnimationTransitionDefinitionList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationTransitionDefinitionList_callbackList[];
extern char igAnimationTransitionDefinitionList_className[];
extern char g_igAnimationTransitionDefinitionList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationTransitionDefinitionList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationTransitionDefinitionList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationTransitionDefinitionList_GetMetaObject,
        igAnimationTransitionDefinitionList_className,
        0x14, /* instance size */
        igAnimationTransitionDefinitionList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationTransitionDefinitionList_callbackList /* callback list */
    );
}
