extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationBindingList_GetVTable[];
extern char thunk_igAnimationBindingList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationBindingList_callbackList[];
extern char igAnimationBindingList_className[];
extern char g_igAnimationBindingList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationBindingList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationBindingList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationBindingList_GetMetaObject,
        igAnimationBindingList_className,
        0x14, /* instance size */
        igAnimationBindingList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationBindingList_callbackList /* callback list */
    );
}
