extern char igCharMetaField_Register[];
extern char igCharArrayMetaField_GetVTable[];
extern char thunk_igCharArrayMetaField_GetMetaObject[];
extern char igCharMetaField_GetPublishedMetaObject[];
extern char g_igCharArrayMetaField_callbackList[];
extern char igCharArrayMetaField_className[];
extern char g_igCharArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igCharArrayMetaField_InitFields();

void igCharArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCharArrayMetaField_metaObject,
        igCharMetaField_Register,
        igCharMetaField_GetPublishedMetaObject,
        thunk_igCharArrayMetaField_GetMetaObject,
        igCharArrayMetaField_className,
        0x38, /* instance size */
        igCharArrayMetaField_GetVTable,
        &igCharArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igCharArrayMetaField_callbackList /* callback list */
    );
}
