extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igStringRefListList_GetVTable[];
extern char thunk_igStringRefListList_GetMetaObject[];
extern char g_igStringRefListList_callbackList[];
extern char igStringRefListList_className[];
extern char g_igStringRefListList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igStringRefListList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStringRefListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igStringRefListList_GetMetaObject,
        igStringRefListList_className,
        0x14, /* instance size */
        igStringRefListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igStringRefListList_callbackList /* callback list */
    );
}
