extern char igBasicColorChanger_GetVTable[];
extern char thunk_igBasicColorChanger_GetMetaObject[];
extern char igColorChanger_GetPublishedMetaObject[];
extern char igColorChanger_Register[];
extern char igBasicColorChanger_className[];
extern char g_igBasicColorChanger_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igBasicColorChanger_InitFields();

void igBasicColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBasicColorChanger_metaObject,
        igColorChanger_Register,
        igColorChanger_GetPublishedMetaObject,
        thunk_igBasicColorChanger_GetMetaObject,
        igBasicColorChanger_className,
        0x58, /* instance size */
        igBasicColorChanger_GetVTable,
        &igBasicColorChanger_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
