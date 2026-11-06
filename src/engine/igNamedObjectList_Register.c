extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igNamedObjectList_GetVTable[];
extern char thunk_igNamedObjectList_GetMetaObject[];
extern char g_igNamedObjectList_callbackList[];
extern char igNamedObjectList_className[];
extern char g_igNamedObjectList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igNamedObjectList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNamedObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igNamedObjectList_GetMetaObject,
        igNamedObjectList_className,
        0x14, /* instance size */
        igNamedObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNamedObjectList_callbackList /* callback list */
    );
}
