extern char igObjectList_GetPublishedMetaObject[];
extern char igCustomStateCollection_GetVTable[];
extern char thunk_igCustomStateCollection_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igCustomStateCollection_callbackList[];
extern char igCustomStateCollection_className[];
extern char g_igCustomStateCollection_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igCustomStateCollection_InitFields();

void igCustomStateCollection_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCustomStateCollection_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCustomStateCollection_GetMetaObject,
        igCustomStateCollection_className,
        0x1C, /* instance size */
        igCustomStateCollection_GetVTable,
        &igCustomStateCollection_InitFields,
        0, /* extra callback item */
        g_igCustomStateCollection_callbackList /* callback list */
    );
}
