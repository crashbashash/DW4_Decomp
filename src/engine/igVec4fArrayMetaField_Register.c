extern char igVec4fMetaField_Register[];
extern char igVec4fArrayMetaField_GetVTable[];
extern char thunk_igVec4fArrayMetaField_GetMetaObject[];
extern char igVec4fMetaField_GetPublishedMetaObject[];
extern char g_igVec4fArrayMetaField_callbackList[];
extern char igVec4fArrayMetaField_className[];
extern char g_igVec4fArrayMetaField_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
int igVec4fArrayMetaField_InitFields();

void igVec4fArrayMetaField_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVec4fArrayMetaField_metaObject,
        igVec4fMetaField_Register,
        igVec4fMetaField_GetPublishedMetaObject,
        thunk_igVec4fArrayMetaField_GetMetaObject,
        igVec4fArrayMetaField_className,
        0x38, /* instance size */
        igVec4fArrayMetaField_GetVTable,
        &igVec4fArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igVec4fArrayMetaField_callbackList /* callback list */
    );
}
