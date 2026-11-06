extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igRenderDestinationAttr_GetVTable[];
extern char thunk_igRenderDestinationAttr_GetMetaObject[];
extern char g_igRenderDestinationAttr_callbackList[];
extern char igRenderDestinationAttr_className[];
extern char g_igRenderDestinationAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igRenderDestinationAttr_InitFields();

void igRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRenderDestinationAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igRenderDestinationAttr_GetMetaObject,
        igRenderDestinationAttr_className,
        0x44, /* instance size */
        igRenderDestinationAttr_GetVTable,
        &igRenderDestinationAttr_InitFields,
        0, /* extra callback item */
        g_igRenderDestinationAttr_callbackList /* callback list */
    );
}
