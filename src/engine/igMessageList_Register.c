extern char igObjectList_GetPublishedMetaObject[];
extern char igMessageList_GetVTable[];
extern char thunk_igMessageList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igMessageList_callbackList[];
extern char igMessageList_className[];
extern char g_igMessageList_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igMessageList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMessageList_GetMetaObject,
        igMessageList_className,
        0x14, /* instance size */
        igMessageList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMessageList_callbackList /* callback list */
    );
}
