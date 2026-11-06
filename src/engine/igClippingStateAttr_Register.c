extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igClippingStateAttr_GetVTable[];
extern char thunk_igClippingStateAttr_GetMetaObject[];
extern char igClippingStateAttr_className[];
extern char g_igClippingStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igClippingStateAttr_InitFields();

void igClippingStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igClippingStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igClippingStateAttr_GetMetaObject,
        igClippingStateAttr_className,
        0x10, /* instance size */
        igClippingStateAttr_GetVTable,
        &igClippingStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
