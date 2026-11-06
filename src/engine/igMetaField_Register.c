extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igMetaField_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMetaField_callbackList[];
extern char igMetaField_className[];
extern char g_igMetaField_metaObject[];
int igMetaObject_RegisterClass();
int igMetaField_InitFields();

void igMetaField_Register(void) {
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igMetaField_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMetaField_GetMetaObject,
        igMetaField_className,
        0x34, /* instance size */
        0,
        &igMetaField_InitFields,
        0, /* extra callback item */
        g_igMetaField_callbackList /* callback list */
    );
}
