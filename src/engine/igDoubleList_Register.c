extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igDoubleList_GetVTable[];
extern char thunk_igDoubleList_GetMetaObject[];
extern char igDoubleList_className[];
extern char g_igDoubleList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002c9510(void);
void igDoubleList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDoubleList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igDoubleList_GetMetaObject,
        igDoubleList_className,
        0x14, /* instance size */
        igDoubleList_GetVTable,
        FUN_002c9510,
        0, /* extra callback item */
        0 /* callback list */
    );
}
