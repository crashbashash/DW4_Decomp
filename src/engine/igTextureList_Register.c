extern char igObjectList_GetPublishedMetaObject[];
extern char igTextureList_GetVTable[];
extern char thunk_igTextureList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igTextureList_callbackList[];
extern char igTextureList_className[];
extern char g_igTextureList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igTextureList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextureList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igTextureList_GetMetaObject,
        igTextureList_className,
        0x14, /* instance size */
        igTextureList_GetVTable,
        0,
        0, /* extra callback item */
        g_igTextureList_callbackList /* callback list */
    );
}
