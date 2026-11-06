extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igBlendFunctionAttr_GetVTable[];
extern char thunk_igBlendFunctionAttr_GetMetaObject[];
extern char g_igBlendFunctionAttr_callbackList[];
extern char igBlendFunctionAttr_className[];
extern char g_igBlendFunctionAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBlendFunctionAttr_InitFields();

void igBlendFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBlendFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igBlendFunctionAttr_GetMetaObject,
        igBlendFunctionAttr_className,
        0x34, /* instance size */
        igBlendFunctionAttr_GetVTable,
        &igBlendFunctionAttr_InitFields,
        0, /* extra callback item */
        g_igBlendFunctionAttr_callbackList /* callback list */
    );
}
