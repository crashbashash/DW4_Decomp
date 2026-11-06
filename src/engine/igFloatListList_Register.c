extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igFloatListList_GetVTable[];
extern char thunk_igFloatListList_GetMetaObject[];
extern char g_igFloatListList_callbackList[];
extern char igFloatListList_className[];
extern char g_igFloatListList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igFloatListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFloatListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igFloatListList_GetMetaObject,
        igFloatListList_className,
        0x14, /* instance size */
        igFloatListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFloatListList_callbackList /* callback list */
    );
}
