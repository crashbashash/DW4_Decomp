extern char igVolume_Register[];
extern char igVolume_GetPublishedMetaObject[];
extern char igAABox_GetVTable[];
extern char thunk_igAABox_GetMetaObject[];
extern char thunk_FUN_0018a8f0[];
extern char igAABox_className[];
extern char g_igAABox_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
int igAABox_InitFields();

void igAABox_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAABox_metaObject,
        igVolume_Register,
        igVolume_GetPublishedMetaObject,
        thunk_igAABox_GetMetaObject,
        igAABox_className,
        0x20, /* instance size */
        igAABox_GetVTable,
        &igAABox_InitFields,
        thunk_FUN_0018a8f0, /* extra callback item */
        0 /* callback list */
    );
}
