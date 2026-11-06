extern char igStringMetaField_Register[];
extern char igStringArrayMetaField_GetVTable[];
extern char thunk_igStringArrayMetaField_GetMetaObject[];
extern char igStringMetaField_GetPublishedMetaObject[];
extern char g_igStringArrayMetaField_callbackList[];
extern char igStringArrayMetaField_className[];
extern char g_igStringArrayMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igStringArrayMetaField_InitFields();

void igStringArrayMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStringArrayMetaField_metaObject,
        igStringMetaField_Register,
        igStringMetaField_GetPublishedMetaObject,
        thunk_igStringArrayMetaField_GetMetaObject,
        igStringArrayMetaField_className,
        0x40, /* instance size */
        igStringArrayMetaField_GetVTable,
        &igStringArrayMetaField_InitFields,
        0, /* extra callback item */
        g_igStringArrayMetaField_callbackList /* callback list */
    );
}
