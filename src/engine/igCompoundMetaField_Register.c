extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char thunk_igCompoundMetaField_GetMetaObject[];
extern char g_igCompoundMetaField_callbackList[];
extern char igCompoundMetaField_className[];
extern char g_igCompoundMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igCompoundMetaField_InitFields();

void igCompoundMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igCompoundMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igCompoundMetaField_GetMetaObject,
        igCompoundMetaField_className,
        0x38, /* instance size */
        0,
        &igCompoundMetaField_InitFields,
        0, /* extra callback item */
        g_igCompoundMetaField_callbackList /* callback list */
    );
}
