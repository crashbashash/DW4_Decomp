extern char igObject_GetMetaObject_ParentAccessor[];
extern char igCompoundList_GetVTable[];
extern char thunk_igCompoundList_GetMetaObject[];
extern char igObject_Register[];
extern char igCompoundList_className[];
extern char g_igCompoundList_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igCompoundList_InitFields();

void igCompoundList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCompoundList_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCompoundList_GetMetaObject,
        igCompoundList_className,
        0x14, /* instance size */
        igCompoundList_GetVTable,
        &igCompoundList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
