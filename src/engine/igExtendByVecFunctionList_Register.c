extern char igDataList_GetPublishedMetaObject[];
extern char igExtendByVecFunctionList_GetVTable[];
extern char thunk_igExtendByVecFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igExtendByVecFunctionList_className[];
extern char g_igExtendByVecFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igExtendByVecFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igExtendByVecFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igExtendByVecFunctionList_GetMetaObject,
        igExtendByVecFunctionList_className,
        0x14, /* instance size */
        igExtendByVecFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
