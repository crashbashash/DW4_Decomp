extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igIterator_GetMetaObject[];
extern char igObject_Register[];
extern char igIterator_className[];
extern char g_igIterator_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igIterator_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igIterator_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igIterator_GetMetaObject,
        igIterator_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
