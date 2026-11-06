extern char igEnumMetaField_Register[];
extern char igEnumArrayMetaField_GetVTable[];
extern char thunk_igEnumArrayMetaField_GetMetaObject[];
extern char igEnumMetaField_GetPublishedMetaObject[];
extern char g_igEnumArrayMetaField_callbackList[];
extern char igEnumArrayMetaField_className[];
extern char g_igEnumArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igEnumArrayMetaField_InitFields();

void igEnumArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEnumArrayMetaField_metaObject,
        igEnumMetaField_Register,
        igEnumMetaField_GetPublishedMetaObject,
        thunk_igEnumArrayMetaField_GetMetaObject,
        igEnumArrayMetaField_className,
        0x3C, /* instance size */
        igEnumArrayMetaField_GetVTable,
        &igEnumArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igEnumArrayMetaField_callbackList /* callback list */
    );
}
