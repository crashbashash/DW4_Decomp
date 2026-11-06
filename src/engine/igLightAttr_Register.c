extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igLightAttr_GetVTable[];
extern char thunk_igLightAttr_GetMetaObject[];
extern char g_igLightAttr_callbackList[];
extern char igLightAttr_className[];
extern char g_igLightAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLightAttr_InitFields();

void igLightAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igLightAttr_GetMetaObject,
        igLightAttr_className,
        0x94, /* instance size */
        igLightAttr_GetVTable,
        &igLightAttr_InitFields,
        0, /* extra callback item */
        g_igLightAttr_callbackList /* callback list */
    );
}
