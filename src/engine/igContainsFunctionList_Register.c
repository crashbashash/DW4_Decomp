extern char igDataList_GetPublishedMetaObject[];
extern char igContainsFunctionList_GetVTable[];
extern char thunk_igContainsFunctionList_GetMetaObject[];
extern char igDataList_Register[];
extern char igContainsFunctionList_className[];
extern char g_igContainsFunctionList_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igContainsFunctionList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igContainsFunctionList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igContainsFunctionList_GetMetaObject,
        igContainsFunctionList_className,
        0x14, /* instance size */
        igContainsFunctionList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
