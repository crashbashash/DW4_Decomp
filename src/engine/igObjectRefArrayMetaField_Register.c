extern char igObjectRefMetaField_Register[];
extern char igObjectRefArrayMetaField_GetVTable[];
extern char thunk_igObjectRefArrayMetaField_GetMetaObject[];
extern char igObjectRefMetaField_GetPublishedMetaObject[];
extern char g_igObjectRefArrayMetaField_callbackList[];
extern char igObjectRefArrayMetaField_className[];
extern char g_igObjectRefArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igObjectRefArrayMetaField_InitFields();

void igObjectRefArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igObjectRefArrayMetaField_metaObject,
        igObjectRefMetaField_Register,
        igObjectRefMetaField_GetPublishedMetaObject,
        thunk_igObjectRefArrayMetaField_GetMetaObject,
        igObjectRefArrayMetaField_className,
        0x48, /* instance size */
        igObjectRefArrayMetaField_GetVTable,
        &igObjectRefArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igObjectRefArrayMetaField_callbackList /* callback list */
    );
}
