extern char igQueue_Register[];
extern char thunk_igStandardQueue_GetMetaObject[];
extern char igStandardQueue_GetVTable[];
extern char igQueue_GetPublishedMetaObject[];
extern char g_igStandardQueue_callbackList[];
extern char igStandardQueue_className[];
extern char g_igStandardQueue_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStandardQueue_InitFields();

void igStandardQueue_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStandardQueue_metaObject,
        igQueue_Register,
        igQueue_GetPublishedMetaObject,
        thunk_igStandardQueue_GetMetaObject,
        igStandardQueue_className,
        0x2C, /* instance size */
        igStandardQueue_GetVTable,
        &igStandardQueue_InitFields,
        0, /* extra callback item */
        g_igStandardQueue_callbackList /* callback list */
    );
}
