extern char igObjectList_GetPublishedMetaObject[];
extern char igStringObjList_GetVTable[];
extern char thunk_igStringObjList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igStringObjList_callbackList[];
extern char igStringObjList_className[];
extern char g_igStringObjList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igStringObjList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStringObjList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igStringObjList_GetMetaObject,
        igStringObjList_className,
        0x14, /* instance size */
        igStringObjList_GetVTable,
        0,
        0, /* extra callback item */
        g_igStringObjList_callbackList /* callback list */
    );
}
