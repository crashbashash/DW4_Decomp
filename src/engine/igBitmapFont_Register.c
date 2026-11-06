extern char igFont_Register[];
extern char igBitmapFont_GetVTable[];
extern char thunk_igBitmapFont_GetMetaObject[];
extern char igFont_GetPublishedMetaObject[];
extern char g_igBitmapFont_callbackList[];
extern char igBitmapFont_className[];
extern char g_igBitmapFont_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igBitmapFont_InitFields();

void igBitmapFont_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBitmapFont_metaObject,
        igFont_Register,
        igFont_GetPublishedMetaObject,
        thunk_igBitmapFont_GetMetaObject,
        igBitmapFont_className,
        0x24, /* instance size */
        igBitmapFont_GetVTable,
        &igBitmapFont_InitFields,
        0, /* extra callback item */
        g_igBitmapFont_callbackList /* callback list */
    );
}
