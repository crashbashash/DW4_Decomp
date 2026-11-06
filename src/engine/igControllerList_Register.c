extern char igObjectList_GetPublishedMetaObject[];
extern char igControllerList_GetVTable[];
extern char thunk_igControllerList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igControllerList_callbackList[];
extern char igControllerList_className[];
extern char g_igControllerList_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igControllerList_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igControllerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igControllerList_GetMetaObject,
        igControllerList_className,
        0x14, /* instance size */
        igControllerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igControllerList_callbackList /* callback list */
    );
}
