extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igBoolList_GetVTable[];
extern char thunk_igBoolList_GetMetaObject[];
extern char igBoolList_className[];
extern char g_igBoolList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002cb280(void);
void igBoolList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoolList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igBoolList_GetMetaObject,
        igBoolList_className,
        0x14, /* instance size */
        igBoolList_GetVTable,
        FUN_002cb280,
        0, /* extra callback item */
        0 /* callback list */
    );
}
