extern char igDataList_GetPublishedMetaObject[];
extern char igObjectList_GetVTable[];
extern char thunk_igObjectList_GetMetaObject[];
extern char igDataList_Register[];
extern char igObjectList_className[];
extern char g_igObjectList_metaObject[];
int FUN_002b5d50();
void *igMetaObject_RegisterClass();
extern int igObjectList_InitFields[4];
void *igObjectList_Register(void) {
    FUN_002b5d50();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igObjectList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igObjectList_GetMetaObject,
        igObjectList_className,
        0x14, /* instance size */
        igObjectList_GetVTable,
        igObjectList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
