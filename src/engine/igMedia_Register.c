extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igMedia_GetMetaObject[];
extern char thunk_FUN_002ebcf0[];
extern char igObject_Register[];
extern char igMedia_className[];
extern char g_igMedia_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igMedia_InitFields_002c1810[4];
void igMedia_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igMedia_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMedia_GetMetaObject,
        igMedia_className,
        8, /* instance size */
        0,
        &igMedia_InitFields_002c1810[0],
        thunk_FUN_002ebcf0, /* extra callback item */
        0 /* callback list */
    );
}
