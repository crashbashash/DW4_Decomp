extern char igUnsignedShortMetaField_Register[];
extern char igUnsignedShortArrayMetaField_GetVTable[];
extern char thunk_igUnsignedShortArrayMetaField_GetMetaObject[];
extern char igUnsignedShortMetaField_GetPublishedMetaObject[];
extern char g_igUnsignedShortArrayMetaField_callbackList[];
extern char igUnsignedShortArrayMetaField_className[];
extern char g_igUnsignedShortArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igUnsignedShortArrayMetaField_InitFields();

void igUnsignedShortArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedShortArrayMetaField_metaObject,
        igUnsignedShortMetaField_Register,
        igUnsignedShortMetaField_GetPublishedMetaObject,
        thunk_igUnsignedShortArrayMetaField_GetMetaObject,
        igUnsignedShortArrayMetaField_className,
        0x38, /* instance size */
        igUnsignedShortArrayMetaField_GetVTable,
        &igUnsignedShortArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igUnsignedShortArrayMetaField_callbackList /* callback list */
    );
}
