extern char igMetaField_GetPublishedMetaObject[];
extern char igVec3fMetaField_GetVTable[];
extern char thunk_igVec3fMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igVec3fMetaField_callbackList[];
extern char igVec3fMetaField_className[];
extern char g_igVec3fMetaField_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();

void igVec3fMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec3fMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVec3fMetaField_GetMetaObject,
        igVec3fMetaField_className,
        0x34, /* instance size */
        igVec3fMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igVec3fMetaField_callbackList /* callback list */
    );
}
