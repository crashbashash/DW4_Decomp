extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igFogStateAttr_GetVTable[];
extern char thunk_igFogStateAttr_GetMetaObject[];
extern char igFogStateAttr_className[];
extern char g_igFogStateAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igFogStateAttr_InitFields();

void igFogStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFogStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igFogStateAttr_GetMetaObject,
        igFogStateAttr_className,
        0x10, /* instance size */
        igFogStateAttr_GetVTable,
        &igFogStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
