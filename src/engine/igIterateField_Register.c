extern char igIterator_Register[];
extern char igIterator_GetPublishedMetaObject[];
extern char igIterateField_GetVTable[];
extern char thunk_igIterateField_GetMetaObject[];
extern char g_igIterateField_callbackList[];
extern char igIterateField_className[];
extern char g_igIterateField_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igIterateField_InitFields();

void igIterateField_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIterateField_metaObject,
        igIterator_Register,
        igIterator_GetPublishedMetaObject,
        thunk_igIterateField_GetMetaObject,
        igIterateField_className,
        0x10, /* instance size */
        igIterateField_GetVTable,
        &igIterateField_InitFields,
        0, /* extra callback item */
        g_igIterateField_callbackList /* callback list */
    );
}
