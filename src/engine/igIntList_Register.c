extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igIntList_GetVTable[];
extern char thunk_igIntList_GetMetaObject[];
extern char igIntList_className[];
extern char g_igIntList_metaObject[];
int FUN_002b5d50();
void *igMetaObject_RegisterClass();
extern int igIntList_InitFields[4];
void *igIntList_Register(void) {
    FUN_002b5d50();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIntList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igIntList_GetMetaObject,
        igIntList_className,
        0x14, /* instance size */
        igIntList_GetVTable,
        igIntList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
