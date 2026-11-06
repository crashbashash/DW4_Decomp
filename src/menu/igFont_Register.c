extern char igNamedObject_GetPublishedMetaObject[];
int igNamedObject_Register();
int thunk_igFont_GetMetaObject();
extern char g_igFont_callbackList[];
extern char igFont_className[];
extern char g_igFont_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igFont_InitFields();

void igFont_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igFont_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igFont_GetMetaObject,
        igFont_className,
        0x1C, /* instance size */
        0,
        &igFont_InitFields,
        0, /* extra callback item */
        g_igFont_callbackList /* callback list */
    );
}
