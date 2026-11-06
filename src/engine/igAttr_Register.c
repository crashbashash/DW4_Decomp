extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igAttr_GetMetaObject[];
extern char FUN_0013b240[];
extern char igObject_Register[];
extern char igAttr_className[];
extern char g_igAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAttr_InitFields();

void igAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAttr_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAttr_GetMetaObject,
        igAttr_className,
        0xC, /* instance size */
        0,
        &igAttr_InitFields,
        FUN_0013b240, /* extra callback item */
        0 /* callback list */
    );
}
