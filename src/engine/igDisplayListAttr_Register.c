extern char igAttr_GetPublishedMetaObject[];
extern char igDisplayListAttr_GetVTable[];
extern char thunk_igDisplayListAttr_GetMetaObject[];
extern char igAttr_Register[];
extern char g_igDisplayListAttr_callbackList[];
extern char igDisplayListAttr_className[];
extern char g_igDisplayListAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igDisplayListAttr_InitFields();

void igDisplayListAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDisplayListAttr_metaObject,
        igAttr_Register,
        igAttr_GetPublishedMetaObject,
        thunk_igDisplayListAttr_GetMetaObject,
        igDisplayListAttr_className,
        0x10, /* instance size */
        igDisplayListAttr_GetVTable,
        &igDisplayListAttr_InitFields,
        0, /* extra callback item */
        g_igDisplayListAttr_callbackList /* callback list */
    );
}
