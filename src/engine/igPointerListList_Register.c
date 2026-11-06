extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igPointerListList_GetVTable[];
extern char thunk_igPointerListList_GetMetaObject[];
extern char g_igPointerListList_callbackList[];
extern char igPointerListList_className[];
extern char g_igPointerListList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igPointerListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPointerListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igPointerListList_GetMetaObject,
        igPointerListList_className,
        0x14, /* instance size */
        igPointerListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igPointerListList_callbackList /* callback list */
    );
}
