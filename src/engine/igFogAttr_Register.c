extern char igVisualAttribute_Register[];
extern char igVisualAttribute_GetPublishedMetaObject[];
extern char igFogAttr_GetVTable[];
extern char thunk_igFogAttr_GetMetaObject[];
extern char igFogAttr_className[];
extern char g_igFogAttr_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igFogAttr_InitFields();

void igFogAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFogAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igFogAttr_GetMetaObject,
        igFogAttr_className,
        0x2C, /* instance size */
        igFogAttr_GetVTable,
        &igFogAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
