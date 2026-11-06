extern char igRenderer_GetPublishedMetaObject[];
extern char igClearRenderer_GetVTable[];
extern char thunk_igClearRenderer_GetMetaObject[];
extern char igRenderer_Register[];
extern char igClearRenderer_className[];
extern char g_igClearRenderer_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igClearRenderer_InitFields();

void igClearRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igClearRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igClearRenderer_GetMetaObject,
        igClearRenderer_className,
        0x10, /* instance size */
        igClearRenderer_GetVTable,
        &igClearRenderer_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
