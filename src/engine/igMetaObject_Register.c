extern char igObject_GetMetaObject_ParentAccessor[];
extern char igMetaObject_GetVTable[];
extern char thunk_igMetaObject_GetMetaObject[];
extern char igObject_Register[];
extern char g_igMetaObject_callbackList[];
extern char igMetaObject_className[];
extern char g_igMetaObject_metaObject[];
int igMetaObject_RegisterClass();
int igMetaObject_InitFields();

void igMetaObject_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMetaObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMetaObject_GetMetaObject,
        igMetaObject_className,
        0x64, /* instance size */
        igMetaObject_GetVTable,
        &igMetaObject_InitFields,
        0, /* extra callback item */
        g_igMetaObject_callbackList /* callback list */
    );
}
