extern char igObjectList_GetPublishedMetaObject[];
extern char igListenerListList_GetVTable[];
extern char thunk_igListenerListList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igListenerListList_callbackList[];
extern char igListenerListList_className[];
extern char g_igListenerListList_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igListenerListList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igListenerListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igListenerListList_GetMetaObject,
        igListenerListList_className,
        0x14, /* instance size */
        igListenerListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igListenerListList_callbackList /* callback list */
    );
}
