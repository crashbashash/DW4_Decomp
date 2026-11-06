extern char igDataList_GetPublishedMetaObject[];
extern char igContainsVecFunctionList_GetVTable[];
extern char thunk_igContainsVecFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igContainsVecFunctionList_className[];
extern char g_igContainsVecFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igContainsVecFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igContainsVecFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igContainsVecFunctionList_GetMetaObject,
        igContainsVecFunctionList_className,
        0x14, /* instance size */
        igContainsVecFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
