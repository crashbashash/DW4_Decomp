extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igPointerList_GetVTable[];
extern char thunk_igPointerList_GetMetaObject[];
extern char igPointerList_className[];
extern char g_igPointerList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igPointerList_InitFields_002c92e0[4];
void igPointerList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPointerList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igPointerList_GetMetaObject,
        igPointerList_className,
        0x14, /* instance size */
        igPointerList_GetVTable,
        &igPointerList_InitFields_002c92e0[0], /* Field adder. */
        0,                                     /* extra callback-vector item (none) */
        0                                      /* zero-terminated callback-vector item list (none) */
    );
}
