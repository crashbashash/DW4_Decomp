extern char igObjectList_GetPublishedMetaObject[];
extern char igListenerList_GetVTable[];
extern char thunk_igListenerList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igListenerList_callbackList[];
extern char igListenerList_className[];
extern char g_igListenerList_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igListenerList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igListenerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igListenerList_GetMetaObject,
        igListenerList_className,
        0x14, /* instance size */
        igListenerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igListenerList_callbackList /* callback list */
    );
}
