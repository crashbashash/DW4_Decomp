extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationList_GetVTable[];
extern char thunk_igAnimationList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationList_callbackList[];
extern char igAnimationList_className[];
extern char g_igAnimationList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationList_GetMetaObject,
        igAnimationList_className,
        0x14, /* instance size */
        igAnimationList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationList_callbackList /* callback list */
    );
}
