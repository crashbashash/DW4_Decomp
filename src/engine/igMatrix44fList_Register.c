extern char igDataList_GetPublishedMetaObject[];
extern char igMatrix44fList_GetVTable[];
extern char thunk_igMatrix44fList_GetMetaObject[];
extern char igDataList_Register[];
extern char igMatrix44fList_className[];
extern char g_igMatrix44fList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
extern int igMatrix44fList_InitFields_00189b10[4];
void igMatrix44fList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrix44fList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igMatrix44fList_GetMetaObject,
        igMatrix44fList_className,
        0x14, /* instance size */
        igMatrix44fList_GetVTable,
        &igMatrix44fList_InitFields_00189b10[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}
