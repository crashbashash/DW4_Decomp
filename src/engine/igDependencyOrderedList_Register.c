extern char igObject_GetMetaObject_ParentAccessor[];
extern char igDependencyOrderedList_GetVTable[];
extern char thunk_igDependencyOrderedList_GetMetaObject[];
extern char igObject_Register[];
extern char g_igDependencyOrderedList_callbackList[];
extern char igDependencyOrderedList_className[];
extern char g_igDependencyOrderedList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igDependencyOrderedList_InitFields();

void igDependencyOrderedList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDependencyOrderedList_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDependencyOrderedList_GetMetaObject,
        igDependencyOrderedList_className,
        0x1C, /* instance size */
        igDependencyOrderedList_GetVTable,
        &igDependencyOrderedList_InitFields,
        0, /* extra callback item */
        g_igDependencyOrderedList_callbackList /* callback list */
    );
}
