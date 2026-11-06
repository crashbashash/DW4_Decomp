extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMetaObjectList_GetVTable[];
extern char thunk_igMetaObjectList_GetMetaObject[];
extern char g_igMetaObjectList_callbackList[];
extern char igMetaObjectList_className[];
extern char g_igMetaObjectList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMetaObjectList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMetaObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMetaObjectList_GetMetaObject,
        igMetaObjectList_className,
        0x14, /* instance size */
        igMetaObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMetaObjectList_callbackList /* callback list */
    );
}
