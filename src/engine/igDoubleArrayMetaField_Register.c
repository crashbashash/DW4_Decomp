extern char igDoubleMetaField_Register[];
extern char igDoubleArrayMetaField_GetVTable[];
extern char thunk_igDoubleArrayMetaField_GetMetaObject[];
extern char igDoubleMetaField_GetPublishedMetaObject[];
extern char g_igDoubleArrayMetaField_callbackList[];
extern char igDoubleArrayMetaField_className[];
extern char g_igDoubleArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igDoubleArrayMetaField_InitFields();

void igDoubleArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDoubleArrayMetaField_metaObject,
        igDoubleMetaField_Register,
        igDoubleMetaField_GetPublishedMetaObject,
        thunk_igDoubleArrayMetaField_GetMetaObject,
        igDoubleArrayMetaField_className,
        0x38, /* instance size */
        igDoubleArrayMetaField_GetVTable,
        &igDoubleArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igDoubleArrayMetaField_callbackList /* callback list */
    );
}
