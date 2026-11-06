extern char igRawRefMetaField_Register[];
extern char igRawRefArrayMetaField_GetVTable[];
extern char thunk_igRawRefArrayMetaField_GetMetaObject[];
extern char igRawRefMetaField_GetPublishedMetaObject[];
extern char g_igRawRefArrayMetaField_callbackList[];
extern char igRawRefArrayMetaField_className[];
extern char g_igRawRefArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igRawRefArrayMetaField_InitFields();

void igRawRefArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRawRefArrayMetaField_metaObject,
        igRawRefMetaField_Register,
        igRawRefMetaField_GetPublishedMetaObject,
        thunk_igRawRefArrayMetaField_GetMetaObject,
        igRawRefArrayMetaField_className,
        0x3C, /* instance size */
        igRawRefArrayMetaField_GetVTable,
        &igRawRefArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igRawRefArrayMetaField_callbackList /* callback list */
    );
}
