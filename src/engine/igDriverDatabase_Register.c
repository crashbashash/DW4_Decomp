extern char igObject_GetMetaObject_ParentAccessor[];
extern char igDriverDatabase_GetVTable[];
extern char thunk_igDriverDatabase_GetMetaObject[];
extern char igObject_Register[];
extern char g_igDriverDatabase_callbackList[];
extern char igDriverDatabase_className[];
extern char g_igDriverDatabase_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igDriverDatabase_InitFields();

void igDriverDatabase_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDriverDatabase_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDriverDatabase_GetMetaObject,
        igDriverDatabase_className,
        0x38, /* instance size */
        igDriverDatabase_GetVTable,
        &igDriverDatabase_InitFields,
        0, /* extra callback item */
        g_igDriverDatabase_callbackList /* callback list */
    );
}
