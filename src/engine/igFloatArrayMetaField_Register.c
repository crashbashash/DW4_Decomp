extern char igFloatMetaField_Register[];
extern char igFloatArrayMetaField_GetVTable[];
extern char thunk_igFloatArrayMetaField_GetMetaObject[];
extern char igFloatMetaField_GetPublishedMetaObject[];
extern char g_igFloatArrayMetaField_callbackList[];
extern char igFloatArrayMetaField_className[];
extern char g_igFloatArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igFloatArrayMetaField_InitFields();

void igFloatArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFloatArrayMetaField_metaObject,
        igFloatMetaField_Register,
        igFloatMetaField_GetPublishedMetaObject,
        thunk_igFloatArrayMetaField_GetMetaObject,
        igFloatArrayMetaField_className,
        0x38, /* instance size */
        igFloatArrayMetaField_GetVTable,
        &igFloatArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igFloatArrayMetaField_callbackList /* callback list */
    );
}
