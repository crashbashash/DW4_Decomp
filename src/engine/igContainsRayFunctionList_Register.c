extern char igDataList_GetPublishedMetaObject[];
extern char igContainsRayFunctionList_GetVTable[];
extern char thunk_igContainsRayFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igContainsRayFunctionList_className[];
extern char g_igContainsRayFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igContainsRayFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igContainsRayFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igContainsRayFunctionList_GetMetaObject,
        igContainsRayFunctionList_className,
        0x14, /* instance size */
        igContainsRayFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
