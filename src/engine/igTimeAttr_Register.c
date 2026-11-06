extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igTimeAttr_GetVTable[];
extern char thunk_igTimeAttr_GetMetaObject[];
extern char igTimeAttr_className[];
extern char g_igTimeAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTimeAttr_InitFields();

void igTimeAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTimeAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTimeAttr_GetMetaObject,
        igTimeAttr_className,
        0x18, /* instance size */
        igTimeAttr_GetVTable,
        &igTimeAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
