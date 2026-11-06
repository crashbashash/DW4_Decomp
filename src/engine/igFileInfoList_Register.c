extern char igObjectList_GetPublishedMetaObject[];
extern char igFileInfoList_GetVTable[];
extern char thunk_igFileInfoList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igFileInfoList_callbackList[];
extern char igFileInfoList_className[];
extern char g_igFileInfoList_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igFileInfoList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFileInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igFileInfoList_GetMetaObject,
        igFileInfoList_className,
        0x14, /* instance size */
        igFileInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFileInfoList_callbackList /* callback list */
    );
}
