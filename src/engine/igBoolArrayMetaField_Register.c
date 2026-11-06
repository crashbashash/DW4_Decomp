extern char igBoolMetaField_Register[];
extern char igBoolArrayMetaField_GetVTable[];
extern char thunk_igBoolArrayMetaField_GetMetaObject[];
extern char igBoolMetaField_GetPublishedMetaObject[];
extern char g_igBoolArrayMetaField_callbackList[];
extern char igBoolArrayMetaField_className[];
extern char g_igBoolArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igBoolArrayMetaField_InitFields();

void igBoolArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoolArrayMetaField_metaObject,
        igBoolMetaField_Register,
        igBoolMetaField_GetPublishedMetaObject,
        thunk_igBoolArrayMetaField_GetMetaObject,
        igBoolArrayMetaField_className,
        0x38, /* instance size */
        igBoolArrayMetaField_GetVTable,
        &igBoolArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igBoolArrayMetaField_callbackList /* callback list */
    );
}
