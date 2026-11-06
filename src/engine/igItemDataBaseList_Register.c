extern char igCompoundList_Register[];
extern char igItemDataBaseList_GetVTable[];
extern char thunk_igItemDataBaseList_GetMetaObject[];
extern char igCompoundList_GetPublishedMetaObject[];
extern char igItemDataBaseList_className[];
extern char g_igItemDataBaseList_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igItemDataBaseList_InitFields();

void igItemDataBaseList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igItemDataBaseList_metaObject,
        igCompoundList_Register,
        igCompoundList_GetPublishedMetaObject,
        thunk_igItemDataBaseList_GetMetaObject,
        igItemDataBaseList_className,
        0x14, /* instance size */
        igItemDataBaseList_GetVTable,
        &igItemDataBaseList_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
