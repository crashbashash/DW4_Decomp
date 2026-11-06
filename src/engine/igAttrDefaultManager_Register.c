extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igAttrDefaultManager_GetMetaObject[];
extern char igObject_Register[];
extern char igAttrDefaultManager_className[];
extern char g_igAttrDefaultManager_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAttrDefaultManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAttrDefaultManager_GetMetaObject,
        igAttrDefaultManager_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
