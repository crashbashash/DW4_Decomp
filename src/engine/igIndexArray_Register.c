extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igIndexArray_GetMetaObject[];
extern char igObject_Register[];
extern char g_igIndexArray_callbackList[];
extern char igIndexArray_className[];
extern char g_igIndexArray_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igIndexArray_InitFields();

void igIndexArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igIndexArray_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igIndexArray_GetMetaObject,
        igIndexArray_className,
        0x1C, /* instance size */
        0,
        &igIndexArray_InitFields,
        0, /* extra callback item */
        g_igIndexArray_callbackList /* callback list */
    );
}
