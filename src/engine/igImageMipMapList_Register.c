extern char igObjectList_GetPublishedMetaObject[];
extern char igImageMipMapList_GetVTable[];
extern char thunk_igImageMipMapList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igImageMipMapList_callbackList[];
extern char igImageMipMapList_className[];
extern char g_igImageMipMapList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igImageMipMapList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igImageMipMapList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igImageMipMapList_GetMetaObject,
        igImageMipMapList_className,
        0x14, /* instance size */
        igImageMipMapList_GetVTable,
        0,
        0, /* extra callback item */
        g_igImageMipMapList_callbackList /* callback list */
    );
}
