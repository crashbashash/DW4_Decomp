extern char igDataList_GetPublishedMetaObject[];
extern char igIsEmptyFunctionList_GetVTable[];
extern char thunk_igIsEmptyFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igIsEmptyFunctionList_className[];
extern char g_igIsEmptyFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igIsEmptyFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIsEmptyFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igIsEmptyFunctionList_GetMetaObject,
        igIsEmptyFunctionList_className,
        0x14, /* instance size */
        igIsEmptyFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
