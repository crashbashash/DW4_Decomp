extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igImageUtils_GetMetaObject[];
extern char igObject_Register[];
extern char igImageUtils_className[];
extern char g_igImageUtils_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igImageUtils_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igImageUtils_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igImageUtils_GetMetaObject,
        igImageUtils_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
