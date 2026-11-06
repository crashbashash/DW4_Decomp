extern char igCapabilityManager_GetPublishedMetaObject[];
extern char igGenericCapabilityManager_GetVTable[];
extern char thunk_igGenericCapabilityManager_GetMetaObject[];
extern char igCapabilityManager_Register[];
extern char igGenericCapabilityManager_className[];
extern char g_igGenericCapabilityManager_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igGenericCapabilityManager_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGenericCapabilityManager_metaObject,
        igCapabilityManager_Register,
        igCapabilityManager_GetPublishedMetaObject,
        thunk_igGenericCapabilityManager_GetMetaObject,
        igGenericCapabilityManager_className,
        8, /* instance size */
        igGenericCapabilityManager_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
