extern char igIntMetaField_Register[];
extern char igIntArrayMetaField_GetVTable[];
extern char thunk_igIntArrayMetaField_GetMetaObject[];
extern char igIntMetaField_GetPublishedMetaObject[];
extern char g_igIntArrayMetaField_callbackList[];
extern char igIntArrayMetaField_className[];
extern char g_igIntArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igIntArrayMetaField_InitFields();

void igIntArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIntArrayMetaField_metaObject,
        igIntMetaField_Register,
        igIntMetaField_GetPublishedMetaObject,
        thunk_igIntArrayMetaField_GetMetaObject,
        igIntArrayMetaField_className,
        0x38, /* instance size */
        igIntArrayMetaField_GetVTable,
        &igIntArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igIntArrayMetaField_callbackList /* callback list */
    );
}
