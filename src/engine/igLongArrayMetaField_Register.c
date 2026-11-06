extern char igLongMetaField_Register[];
extern char igLongArrayMetaField_GetVTable[];
extern char thunk_igLongArrayMetaField_GetMetaObject[];
extern char igLongMetaField_GetPublishedMetaObject[];
extern char g_igLongArrayMetaField_callbackList[];
extern char igLongArrayMetaField_className[];
extern char g_igLongArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igLongArrayMetaField_InitFields();

void igLongArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLongArrayMetaField_metaObject,
        igLongMetaField_Register,
        igLongMetaField_GetPublishedMetaObject,
        thunk_igLongArrayMetaField_GetMetaObject,
        igLongArrayMetaField_className,
        0x38, /* instance size */
        igLongArrayMetaField_GetVTable,
        &igLongArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igLongArrayMetaField_callbackList /* callback list */
    );
}
