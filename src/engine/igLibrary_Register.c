extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igLibrary_GetMetaObject[];
extern char igObject_Register[];
extern char igLibrary_className[];
extern char g_igLibrary_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igLibrary_InitFields();

void igLibrary_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igLibrary_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igLibrary_GetMetaObject,
        igLibrary_className,
        0xC, /* instance size */
        0,
        &igLibrary_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
