extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igLibraryLoader_GetMetaObject[];
extern char igObject_Register[];
extern char igLibraryLoader_className[];
extern char g_igLibraryLoader_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igLibraryLoader_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igLibraryLoader_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igLibraryLoader_GetMetaObject,
        igLibraryLoader_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
