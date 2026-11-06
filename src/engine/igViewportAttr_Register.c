extern char igVisualAttribute_Register[];
extern char igViewportAttr_GetVTable[];
extern char thunk_igViewportAttr_GetMetaObject[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char g_igViewportAttr_callbackList[];
extern char igViewportAttr_className[];
extern char g_igViewportAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igViewportAttr_InitFields();

void igViewportAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewportAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igViewportAttr_GetMetaObject,
        igViewportAttr_className,
        0x28, /* instance size */
        igViewportAttr_GetVTable,
        &igViewportAttr_InitFields,
        0, /* extra callback item */
        g_igViewportAttr_callbackList /* callback list */
    );
}
