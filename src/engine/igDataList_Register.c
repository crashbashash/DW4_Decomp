extern char igObject_GetMetaObject_ParentAccessor[];
extern char igDataList_GetVTable[];
extern char thunk_igDataList_GetMetaObject[];
extern char igObject_Register[];
extern char igDataList_className[];
extern char g_igDataList_metaObject[];
int FUN_002b5d50();
void *igMetaObject_RegisterClass();
int igDataList_InitFields();

void *igDataList_Register(void) {
    FUN_002b5d50();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDataList_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataList_GetMetaObject,
        igDataList_className,
        0x14, /* instance size */
        igDataList_GetVTable,
        &igDataList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
