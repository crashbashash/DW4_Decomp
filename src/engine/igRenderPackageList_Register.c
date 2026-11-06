extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igRenderPackageList_GetVTable[];
extern char thunk_igRenderPackageList_GetMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char g_igRenderPackageList_callbackList[];
extern char igRenderPackageList_className[];
extern char g_igRenderPackageList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igRenderPackageList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRenderPackageList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igRenderPackageList_GetMetaObject,
        igRenderPackageList_className,
        0x14, /* instance size */
        igRenderPackageList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRenderPackageList_callbackList /* callback list */
    );
}
