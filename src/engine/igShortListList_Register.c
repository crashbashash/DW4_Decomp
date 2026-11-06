extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igShortListList_GetVTable[];
extern char thunk_igShortListList_GetMetaObject[];
extern char g_igShortListList_callbackList[];
extern char igShortListList_className[];
extern char g_igShortListList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igShortListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igShortListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igShortListList_GetMetaObject,
        igShortListList_className,
        0x14, /* instance size */
        igShortListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igShortListList_callbackList /* callback list */
    );
}
