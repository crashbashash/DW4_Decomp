extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igPixelPipelineModeAttr_GetVTable[];
extern char thunk_igPixelPipelineModeAttr_GetMetaObject[];
extern char igPixelPipelineModeAttr_className[];
extern char g_igPixelPipelineModeAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPixelPipelineModeAttr_InitFields();

void igPixelPipelineModeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPixelPipelineModeAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igPixelPipelineModeAttr_GetMetaObject,
        igPixelPipelineModeAttr_className,
        0x10, /* instance size */
        igPixelPipelineModeAttr_GetVTable,
        &igPixelPipelineModeAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
