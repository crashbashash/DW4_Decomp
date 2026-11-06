extern char igInfo_GetPublishedMetaObject[];
extern char igNamedObjectInfo_GetVTable[];
extern char thunk_igNamedObjectInfo_GetMetaObject[];
extern char igInfo_Register[];
extern char g_igNamedObjectInfo_callbackList[];
extern char igNamedObjectInfo_className[];
extern char g_igNamedObjectInfo_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igNamedObjectInfo_InitFields();

void igNamedObjectInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNamedObjectInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        thunk_igNamedObjectInfo_GetMetaObject,
        igNamedObjectInfo_className,
        0x18, /* instance size */
        igNamedObjectInfo_GetVTable,
        &igNamedObjectInfo_InitFields,
        0, /* extra callback item */
        g_igNamedObjectInfo_callbackList /* callback list */
    );
}
