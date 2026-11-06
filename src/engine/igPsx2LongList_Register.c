extern char igDataList_GetPublishedMetaObject[];
extern char igPsx2LongList_GetVTable[];
extern char thunk_igPsx2LongList_GetMetaObject[];
extern char igDataList_Register[];
extern char igPsx2LongList_className[];
extern char g_igPsx2LongList_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
extern int igPsx2LongList_InitFields_00152970[4];
void igPsx2LongList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2LongList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igPsx2LongList_GetMetaObject,
        igPsx2LongList_className,
        0x14, /* instance size */
        igPsx2LongList_GetVTable,
        &igPsx2LongList_InitFields_00152970[0], /* Field adder. */
        0,                                      /* extra callback-vector item (none) */
        0                                       /* zero-terminated callback-vector item list (none) */
    );
}
