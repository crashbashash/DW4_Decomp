extern char igDataList_GetPublishedMetaObject[];
extern char igTransformFunctionList_GetVTable[];
extern char thunk_igTransformFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igTransformFunctionList_className[];
extern char g_igTransformFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igTransformFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTransformFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igTransformFunctionList_GetMetaObject,
        igTransformFunctionList_className,
        0x14, /* instance size */
        igTransformFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
