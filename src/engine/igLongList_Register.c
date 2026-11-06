extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igLongList_GetVTable[];
extern char thunk_igLongList_GetMetaObject[];
extern char igLongList_className[];
extern char g_igLongList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igLongList_InitFields_002ca7f0[4];
void igLongList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLongList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igLongList_GetMetaObject,
        igLongList_className,
        0x14, /* instance size */
        igLongList_GetVTable,
        &igLongList_InitFields_002ca7f0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}
