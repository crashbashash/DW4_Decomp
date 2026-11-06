extern char igUnsignedIntMetaField_Register[];
extern char igUnsignedIntArrayMetaField_GetVTable[];
extern char thunk_igUnsignedIntArrayMetaField_GetMetaObject[];
extern char igUnsignedIntMetaField_GetPublishedMetaObject[];
extern char g_igUnsignedIntArrayMetaField_callbackList[];
extern char igUnsignedIntArrayMetaField_className[];
extern char g_igUnsignedIntArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igUnsignedIntArrayMetaField_InitFields();

void igUnsignedIntArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedIntArrayMetaField_metaObject,
        igUnsignedIntMetaField_Register,
        igUnsignedIntMetaField_GetPublishedMetaObject,
        thunk_igUnsignedIntArrayMetaField_GetMetaObject,
        igUnsignedIntArrayMetaField_className,
        0x38, /* instance size */
        igUnsignedIntArrayMetaField_GetVTable,
        &igUnsignedIntArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igUnsignedIntArrayMetaField_callbackList /* callback list */
    );
}
