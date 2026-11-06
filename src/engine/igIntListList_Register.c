extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igIntListList_GetVTable[];
extern char thunk_igIntListList_GetMetaObject[];
extern char g_igIntListList_callbackList[];
extern char igIntListList_className[];
extern char g_igIntListList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igIntListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIntListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igIntListList_GetMetaObject,
        igIntListList_className,
        0x14, /* instance size */
        igIntListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igIntListList_callbackList /* callback list */
    );
}
