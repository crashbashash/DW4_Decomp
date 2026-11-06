extern char igDataList_GetPublishedMetaObject[];
extern char igNonRefCountedObjectStack_GetVTable[];
extern char thunk_igNonRefCountedObjectStack_GetMetaObject[];
extern char igDataList_Register[];
extern char igNonRefCountedObjectStack_className[];
extern char g_igNonRefCountedObjectStack_metaObject[];
int DataPumpLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
extern int igNonRefCountedObjectStack_InitFields_001e44c0[4];
void igNonRefCountedObjectStack_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedObjectStack_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igNonRefCountedObjectStack_GetMetaObject,
        igNonRefCountedObjectStack_className,
        0x14, /* instance size */
        igNonRefCountedObjectStack_GetVTable,
        &igNonRefCountedObjectStack_InitFields_001e44c0[0], /* Field adder. */
        0,                                                  /* extra callback-vector item (none) */
        0                                                   /* zero-terminated callback-vector item list (none) */
    );
}
