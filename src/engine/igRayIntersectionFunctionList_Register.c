extern char igDataList_GetPublishedMetaObject[];
extern char igRayIntersectionFunctionList_GetVTable[];
extern char thunk_igRayIntersectionFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igRayIntersectionFunctionList_className[];
extern char g_igRayIntersectionFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igRayIntersectionFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRayIntersectionFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igRayIntersectionFunctionList_GetMetaObject,
        igRayIntersectionFunctionList_className,
        0x14, /* instance size */
        igRayIntersectionFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
