extern char igNamedObject_GetPublishedMetaObject[];
extern char thunk_igInfoManager_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igInfoManager_callbackList[];
extern char igInfoManager_className[];
extern char g_igInfoManager_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igInfoManager_InitFields();

void igInfoManager_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInfoManager_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igInfoManager_GetMetaObject,
        igInfoManager_className,
        0x10, /* instance size */
        0,
        &igInfoManager_InitFields,
        0, /* extra callback item */
        g_igInfoManager_callbackList /* callback list */
    );
}
