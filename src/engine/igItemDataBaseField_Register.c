extern char igCompoundMetaField_GetPublishedMetaObject[];
extern char igItemDataBaseField_GetVTable[];
extern char thunk_igItemDataBaseField_GetMetaObject[];
extern char igCompoundMetaField_Register[];
extern char g_igItemDataBaseField_callbackList[];
extern char igItemDataBaseField_className[];
extern char g_igItemDataBaseField_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igItemDataBaseField_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igItemDataBaseField_metaObject,
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igItemDataBaseField_GetMetaObject,
        igItemDataBaseField_className,
        0x38, /* instance size */
        igItemDataBaseField_GetVTable,
        0,
        0, /* extra callback item */
        g_igItemDataBaseField_callbackList /* callback list */
    );
}
