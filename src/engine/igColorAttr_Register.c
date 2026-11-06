extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igColorAttr_GetVTable[];
extern char thunk_igColorAttr_GetMetaObject[];
extern char igColorAttr_className[];
extern char g_igColorAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igColorAttr_InitFields();

void igColorAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igColorAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igColorAttr_GetMetaObject,
        igColorAttr_className,
        0x20, /* instance size */
        igColorAttr_GetVTable,
        &igColorAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
