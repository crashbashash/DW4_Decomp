extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igRenderListAttr_GetVTable[];
extern char thunk_igRenderListAttr_GetMetaObject[];
extern char g_igRenderListAttr_callbackList[];
extern char igRenderListAttr_className[];
extern char g_igRenderListAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igRenderListAttr_InitFields();

void igRenderListAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRenderListAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igRenderListAttr_GetMetaObject,
        igRenderListAttr_className,
        0x14, /* instance size */
        igRenderListAttr_GetVTable,
        &igRenderListAttr_InitFields,
        0, /* extra callback item */
        g_igRenderListAttr_callbackList /* callback list */
    );
}
