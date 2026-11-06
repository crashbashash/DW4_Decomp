extern char igMetaField_GetPublishedMetaObject[];
extern char igMatrix44fMetaField_GetVTable[];
extern char thunk_igMatrix44fMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igMatrix44fMetaField_callbackList[];
extern char igMatrix44fMetaField_className[];
extern char g_igMatrix44fMetaField_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igMatrix44fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrix44fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igMatrix44fMetaField_GetMetaObject,
        igMatrix44fMetaField_className,
        0x34, /* instance size */
        igMatrix44fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igMatrix44fMetaField_callbackList /* callback list */
    );
}
