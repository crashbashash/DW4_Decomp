extern char igObject_GetMetaObject_ParentAccessor[];
extern char igClut_GetVTable[];
extern char thunk_igClut_GetMetaObject[];
extern char igObject_Register[];
extern char igClut_className[];
extern char g_igClut_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igClut_InitFields();

void igClut_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igClut_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igClut_GetMetaObject,
        igClut_className,
        0x20, /* instance size */
        igClut_GetVTable,
        &igClut_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
