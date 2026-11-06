extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igLightingStateAttr_GetVTable[];
extern char thunk_igLightingStateAttr_GetMetaObject[];
extern char igLightingStateAttr_className[];
extern char g_igLightingStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLightingStateAttr_InitFields();

void igLightingStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightingStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igLightingStateAttr_GetMetaObject,
        igLightingStateAttr_className,
        0x10, /* instance size */
        igLightingStateAttr_GetVTable,
        &igLightingStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
