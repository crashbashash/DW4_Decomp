extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igFloatList_GetVTable[];
extern char thunk_igFloatList_GetMetaObject[];
extern char igFloatList_className[];
extern char g_igFloatList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igFloatList_InitFields_002c98f0[4];
void igFloatList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFloatList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igFloatList_GetMetaObject,
        igFloatList_className,
        0x14, /* instance size */
        igFloatList_GetVTable,
        &igFloatList_InitFields_002c98f0[0],
        0, /* extra callback item */
        0 /* callback list */
    );
}
