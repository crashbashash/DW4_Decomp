extern char igShortMetaField_Register[];
extern char igShortArrayMetaField_GetVTable[];
extern char thunk_igShortArrayMetaField_GetMetaObject[];
extern char igShortMetaField_GetPublishedMetaObject[];
extern char g_igShortArrayMetaField_callbackList[];
extern char igShortArrayMetaField_className[];
extern char g_igShortArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igShortArrayMetaField_InitFields();

void igShortArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igShortArrayMetaField_metaObject,
        igShortMetaField_Register,
        igShortMetaField_GetPublishedMetaObject,
        thunk_igShortArrayMetaField_GetMetaObject,
        igShortArrayMetaField_className,
        0x38, /* instance size */
        igShortArrayMetaField_GetVTable,
        &igShortArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igShortArrayMetaField_callbackList /* callback list */
    );
}
