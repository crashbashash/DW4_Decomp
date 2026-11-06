extern char igDataList_GetPublishedMetaObject[];
extern char igDependencyList_GetVTable[];
extern char thunk_igDependencyList_GetMetaObject[];
extern char igDataList_Register[];
extern char igDependencyList_className[];
extern char g_igDependencyList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002c7eb0(void);
void igDependencyList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDependencyList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igDependencyList_GetMetaObject,
        igDependencyList_className,
        0x14, /* instance size */
        igDependencyList_GetVTable,
        FUN_002c7eb0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
