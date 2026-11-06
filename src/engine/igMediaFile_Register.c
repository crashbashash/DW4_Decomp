extern char igFile_GetPublishedMetaObject[];
extern char igMediaFile_GetVTable[];
extern char thunk_igMediaFile_GetMetaObject[];
extern char igFile_Register[];
extern char g_igMediaFile_callbackList[];
extern char igMediaFile_className[];
extern char g_igMediaFile_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igMediaFile_InitFields();

void igMediaFile_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMediaFile_metaObject,
        igFile_Register,
        igFile_GetPublishedMetaObject,
        thunk_igMediaFile_GetMetaObject,
        igMediaFile_className,
        0x44, /* instance size */
        igMediaFile_GetVTable,
        &igMediaFile_InitFields,
        0, /* extra callback item */
        g_igMediaFile_callbackList /* callback list */
    );
}
