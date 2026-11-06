extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char igEnumMetaField_GetVTable[];
extern char thunk_igEnumMetaField_GetMetaObject[];
extern char g_igEnumMetaField_callbackList[];
extern char igEnumMetaField_className[];
extern char g_igEnumMetaField_metaObject[];
int igMetaObject_RegisterClass();
int igEnumMetaField_InitFields();

void igEnumMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEnumMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igEnumMetaField_GetMetaObject,
        igEnumMetaField_className,
        0x38, /* instance size */
        igEnumMetaField_GetVTable,
        &igEnumMetaField_InitFields,
        0, /* extra callback item */
        g_igEnumMetaField_callbackList /* callback list */
    );
}
