extern char igDataList_GetPublishedMetaObject[];
extern char igNonRefCountedObjectList_GetVTable[];
extern char thunk_igNonRefCountedObjectList_GetMetaObject[];
extern char igDataList_Register[];
extern char igNonRefCountedObjectList_className[];
extern char g_igNonRefCountedObjectList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igNonRefCountedObjectList_InitFields_002bddc0[4];
void igNonRefCountedObjectList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedObjectList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igNonRefCountedObjectList_GetMetaObject,
        igNonRefCountedObjectList_className,
        0x14, /* instance size */
        igNonRefCountedObjectList_GetVTable,
        &igNonRefCountedObjectList_InitFields_002bddc0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}
