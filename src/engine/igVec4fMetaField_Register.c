extern char igMetaField_GetPublishedMetaObject[];
extern char igVec4fMetaField_GetVTable[];
extern char thunk_igVec4fMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igVec4fMetaField_callbackList[];
extern char igVec4fMetaField_className[];
extern char g_igVec4fMetaField_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVec4fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec4fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVec4fMetaField_GetMetaObject,
        igVec4fMetaField_className,
        0x34, /* instance size */
        igVec4fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igVec4fMetaField_callbackList /* callback list */
    );
}
