extern char igDataList_GetPublishedMetaObject[];
extern char igGetCenterFunctionList_GetVTable[];
extern char thunk_igGetCenterFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igGetCenterFunctionList_className[];
extern char g_igGetCenterFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igGetCenterFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGetCenterFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igGetCenterFunctionList_GetMetaObject,
        igGetCenterFunctionList_className,
        0x14, /* instance size */
        igGetCenterFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
