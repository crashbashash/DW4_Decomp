extern char igGuiComponent_Register[];
extern char igBoxComponent_GetVTable[];
extern char thunk_igBoxComponent_GetMetaObject[];
extern char igGuiComponent_GetPublishedMetaObject[];
extern char igBoxComponent_className[];
extern char g_igBoxComponent_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igBoxComponent_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoxComponent_metaObject,
        igGuiComponent_Register,
        igGuiComponent_GetPublishedMetaObject,
        thunk_igBoxComponent_GetMetaObject,
        igBoxComponent_className,
        0x24, /* instance size */
        igBoxComponent_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
