extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igCopyRenderDestinationAttr_GetVTable[];
extern char thunk_igCopyRenderDestinationAttr_GetMetaObject[];
extern char g_igCopyRenderDestinationAttr_callbackList[];
extern char igCopyRenderDestinationAttr_className[];
extern char g_igCopyRenderDestinationAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCopyRenderDestinationAttr_InitFields();

void igCopyRenderDestinationAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCopyRenderDestinationAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igCopyRenderDestinationAttr_GetMetaObject,
        igCopyRenderDestinationAttr_className,
        0x34, /* instance size */
        igCopyRenderDestinationAttr_GetVTable,
        &igCopyRenderDestinationAttr_InitFields,
        0, /* extra callback item */
        g_igCopyRenderDestinationAttr_callbackList /* callback list */
    );
}
