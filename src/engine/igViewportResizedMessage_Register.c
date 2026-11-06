extern char igMessage_GetPublishedMetaObject[];
extern char igMessage_Register[];
extern char igViewportResizedMessage_GetVTable[];
extern char thunk_igViewportResizedMessage_GetMetaObject[];
extern char igViewportResizedMessage_className[];
extern char g_igViewportResizedMessage_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igViewportResizedMessage_InitFields();

void igViewportResizedMessage_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewportResizedMessage_metaObject,
        igMessage_Register,
        igMessage_GetPublishedMetaObject,
        thunk_igViewportResizedMessage_GetMetaObject,
        igViewportResizedMessage_className,
        0x18, /* instance size */
        igViewportResizedMessage_GetVTable,
        &igViewportResizedMessage_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
