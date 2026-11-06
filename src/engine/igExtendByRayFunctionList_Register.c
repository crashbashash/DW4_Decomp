extern char igDataList_GetPublishedMetaObject[];
extern char igExtendByRayFunctionList_GetVTable[];
extern char thunk_igExtendByRayFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igExtendByRayFunctionList_className[];
extern char g_igExtendByRayFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igExtendByRayFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igExtendByRayFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igExtendByRayFunctionList_GetMetaObject,
        igExtendByRayFunctionList_className,
        0x14, /* instance size */
        igExtendByRayFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
