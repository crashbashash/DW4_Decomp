extern char igObject_GetMetaObject_ParentAccessor[];
extern char igOptConfiguration_GetVTable[];
extern char thunk_igOptConfiguration_GetMetaObject[];
extern char igObject_Register[];
extern char igOptConfiguration_className[];
extern char g_igOptConfiguration_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igOptConfiguration_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOptConfiguration_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igOptConfiguration_GetMetaObject,
        igOptConfiguration_className,
        8, /* instance size */
        igOptConfiguration_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
