extern char igDataList_GetPublishedMetaObject[];
extern char igEmptyFunctionList_GetVTable[];
extern char thunk_igEmptyFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igEmptyFunctionList_className[];
extern char g_igEmptyFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igEmptyFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEmptyFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igEmptyFunctionList_GetMetaObject,
        igEmptyFunctionList_className,
        0x14, /* instance size */
        igEmptyFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
