extern char igObjectList_GetPublishedMetaObject[];
extern char igCustomStateCollectionList_GetVTable[];
extern char thunk_igCustomStateCollectionList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCustomStateCollectionList_callbackList[];
extern char igCustomStateCollectionList_className[];
extern char g_igCustomStateCollectionList_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igCustomStateCollectionList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCustomStateCollectionList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCustomStateCollectionList_GetMetaObject,
        igCustomStateCollectionList_className,
        0x14, /* instance size */
        igCustomStateCollectionList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCustomStateCollectionList_callbackList /* callback list */
    );
}
