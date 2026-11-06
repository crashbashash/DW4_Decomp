extern char igDataList_GetPublishedMetaObject[];
extern char igQuaternionfList_GetVTable[];
extern char thunk_igQuaternionfList_GetMetaObject[];
extern char igDataList_Register[];
extern char igQuaternionfList_className[];
extern char g_igQuaternionfList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
extern int igQuaternionfList_InitFields_00189d80[4];
void igQuaternionfList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igQuaternionfList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igQuaternionfList_GetMetaObject,
        igQuaternionfList_className,
        0x14, /* instance size */
        igQuaternionfList_GetVTable,
        &igQuaternionfList_InitFields_00189d80[0], /* Field adder. */
        0,                                         /* extra callback-vector item (none) */
        0                                          /* zero-terminated callback-vector item list (none) */
    );
}
