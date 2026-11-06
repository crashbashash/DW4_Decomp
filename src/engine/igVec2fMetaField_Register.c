extern char igMetaField_GetPublishedMetaObject[];
extern char igVec2fMetaField_GetVTable[];
extern char thunk_igVec2fMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igVec2fMetaField_callbackList[];
extern char igVec2fMetaField_className[];
extern char g_igVec2fMetaField_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVec2fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec2fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVec2fMetaField_GetMetaObject,
        igVec2fMetaField_className,
        0x34, /* instance size */
        igVec2fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igVec2fMetaField_callbackList /* callback list */
    );
}
