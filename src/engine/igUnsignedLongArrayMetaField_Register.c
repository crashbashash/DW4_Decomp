extern char igUnsignedLongMetaField_Register[];
extern char igUnsignedLongArrayMetaField_GetVTable[];
extern char thunk_igUnsignedLongArrayMetaField_GetMetaObject[];
extern char igUnsignedLongMetaField_GetPublishedMetaObject[];
extern char g_igUnsignedLongArrayMetaField_callbackList[];
extern char igUnsignedLongArrayMetaField_className[];
extern char g_igUnsignedLongArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igUnsignedLongArrayMetaField_InitFields();

void igUnsignedLongArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedLongArrayMetaField_metaObject,
        igUnsignedLongMetaField_Register,
        igUnsignedLongMetaField_GetPublishedMetaObject,
        thunk_igUnsignedLongArrayMetaField_GetMetaObject,
        igUnsignedLongArrayMetaField_className,
        0x38, /* instance size */
        igUnsignedLongArrayMetaField_GetVTable,
        &igUnsignedLongArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igUnsignedLongArrayMetaField_callbackList /* callback list */
    );
}
