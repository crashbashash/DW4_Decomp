extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igSetRenderDestinationAttr_GetVTable[];
extern char thunk_igSetRenderDestinationAttr_GetMetaObject[];
extern char g_igSetRenderDestinationAttr_callbackList[];
extern char igSetRenderDestinationAttr_className[];
extern char g_igSetRenderDestinationAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igSetRenderDestinationAttr_InitFields();

void igSetRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSetRenderDestinationAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igSetRenderDestinationAttr_GetMetaObject,
        igSetRenderDestinationAttr_className,
        0x10, /* instance size */
        igSetRenderDestinationAttr_GetVTable,
        &igSetRenderDestinationAttr_InitFields,
        0, /* extra callback item */
        g_igSetRenderDestinationAttr_callbackList /* callback list */
    );
}
