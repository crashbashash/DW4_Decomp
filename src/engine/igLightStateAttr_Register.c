extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igLightStateAttr_GetVTable[];
extern char thunk_igLightStateAttr_GetMetaObject[];
extern char g_igLightStateAttr_callbackList[];
extern char igLightStateAttr_className[];
extern char g_igLightStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLightStateAttr_InitFields();

void igLightStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igLightStateAttr_GetMetaObject,
        igLightStateAttr_className,
        0x18, /* instance size */
        igLightStateAttr_GetVTable,
        &igLightStateAttr_InitFields,
        0, /* extra callback item */
        g_igLightStateAttr_callbackList /* callback list */
    );
}
