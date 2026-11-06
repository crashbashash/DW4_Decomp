extern char igUnsignedCharMetaField_Register[];
extern char igUnsignedCharArrayMetaField_GetVTable[];
extern char thunk_igUnsignedCharArrayMetaField_GetMetaObject[];
extern char igUnsignedCharMetaField_GetPublishedMetaObject[];
extern char g_igUnsignedCharArrayMetaField_callbackList[];
extern char igUnsignedCharArrayMetaField_className[];
extern char g_igUnsignedCharArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igUnsignedCharArrayMetaField_InitFields();

void igUnsignedCharArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedCharArrayMetaField_metaObject,
        igUnsignedCharMetaField_Register,
        igUnsignedCharMetaField_GetPublishedMetaObject,
        thunk_igUnsignedCharArrayMetaField_GetMetaObject,
        igUnsignedCharArrayMetaField_className,
        0x38, /* instance size */
        igUnsignedCharArrayMetaField_GetVTable,
        &igUnsignedCharArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igUnsignedCharArrayMetaField_callbackList /* callback list */
    );
}
