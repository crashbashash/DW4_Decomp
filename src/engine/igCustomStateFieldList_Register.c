extern char igObjectList_GetPublishedMetaObject[];
extern char igCustomStateFieldList_GetVTable[];
extern char thunk_igCustomStateFieldList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCustomStateFieldList_callbackList[];
extern char igCustomStateFieldList_className[];
extern char g_igCustomStateFieldList_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igCustomStateFieldList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCustomStateFieldList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCustomStateFieldList_GetMetaObject,
        igCustomStateFieldList_className,
        0x14, /* instance size */
        igCustomStateFieldList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCustomStateFieldList_callbackList /* callback list */
    );
}
