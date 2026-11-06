extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igAlphaStateAttr_GetVTable[];
extern char thunk_igAlphaStateAttr_GetMetaObject[];
extern char igAlphaStateAttr_className[];
extern char g_igAlphaStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAlphaStateAttr_InitFields();

void igAlphaStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAlphaStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igAlphaStateAttr_GetMetaObject,
        igAlphaStateAttr_className,
        0x10, /* instance size */
        igAlphaStateAttr_GetVTable,
        &igAlphaStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
