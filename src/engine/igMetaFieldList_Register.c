extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igMetaFieldList_GetVTable[];
extern char thunk_igMetaFieldList_GetMetaObject[];
extern char g_igMetaFieldList_callbackList[];
extern char igMetaFieldList_className[];
extern char g_igMetaFieldList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igMetaFieldList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMetaFieldList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMetaFieldList_GetMetaObject,
        igMetaFieldList_className,
        0x14, /* instance size */
        igMetaFieldList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMetaFieldList_callbackList /* callback list */
    );
}
