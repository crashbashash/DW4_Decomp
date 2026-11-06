extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMetaObjectListList_GetVTable[];
extern char thunk_igMetaObjectListList_GetMetaObject[];
extern char g_igMetaObjectListList_callbackList[];
extern char igMetaObjectListList_className[];
extern char g_igMetaObjectListList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMetaObjectListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMetaObjectListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMetaObjectListList_GetMetaObject,
        igMetaObjectListList_className,
        0x14, /* instance size */
        igMetaObjectListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMetaObjectListList_callbackList /* callback list */
    );
}
