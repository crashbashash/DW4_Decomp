extern char igVisualContextCapabilityManager_GetVTable[];
extern char thunk_igVisualContextCapabilityManager_GetMetaObject[];
extern char igCapabilityManager_GetPublishedMetaObject[];
extern char igCapabilityManager_Register[];
extern char g_igVisualContextCapabilityManager_callbackList[];
extern char igVisualContextCapabilityManager_className[];
extern char g_igVisualContextCapabilityManager_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVisualContextCapabilityManager_InitFields();

void igVisualContextCapabilityManager_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVisualContextCapabilityManager_metaObject,
        igCapabilityManager_Register,
        igCapabilityManager_GetPublishedMetaObject,
        thunk_igVisualContextCapabilityManager_GetMetaObject,
        igVisualContextCapabilityManager_className,
        0xC, /* instance size */
        igVisualContextCapabilityManager_GetVTable,
        &igVisualContextCapabilityManager_InitFields,
        0, /* extra callback item */
        g_igVisualContextCapabilityManager_callbackList /* callback list */
    );
}
