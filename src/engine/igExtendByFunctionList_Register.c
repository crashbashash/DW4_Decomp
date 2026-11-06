extern char igDataList_GetPublishedMetaObject[];
extern char igExtendByFunctionList_GetVTable[];
extern char thunk_igExtendByFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igExtendByFunctionList_className[];
extern char g_igExtendByFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igExtendByFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igExtendByFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igExtendByFunctionList_GetMetaObject,
        igExtendByFunctionList_className,
        0x14, /* instance size */
        igExtendByFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
