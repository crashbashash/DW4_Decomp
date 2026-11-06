extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igCharList_GetVTable[];
extern char thunk_igCharList_GetMetaObject[];
extern char igCharList_className[];
extern char g_igCharList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002cb010(void);
void igCharList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCharList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igCharList_GetMetaObject,
        igCharList_className,
        0x14, /* instance size */
        igCharList_GetVTable,
        FUN_002cb010,
        0, /* extra callback item */
        0 /* callback list */
    );
}
