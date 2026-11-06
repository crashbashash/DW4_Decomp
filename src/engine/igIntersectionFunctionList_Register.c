extern char igDataList_GetPublishedMetaObject[];
extern char igIntersectionFunctionList_GetVTable[];
extern char thunk_igIntersectionFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igIntersectionFunctionList_className[];
extern char g_igIntersectionFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igIntersectionFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIntersectionFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igIntersectionFunctionList_GetMetaObject,
        igIntersectionFunctionList_className,
        0x14, /* instance size */
        igIntersectionFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
