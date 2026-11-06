extern char igOnOffColorChanger_GetVTable[];
extern char thunk_igOnOffColorChanger_GetMetaObject[];
extern char igBasicColorChanger_GetPublishedMetaObject[];
extern char igBasicColorChanger_Register[];
extern char igOnOffColorChanger_className[];
extern char g_igOnOffColorChanger_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igOnOffColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffColorChanger_metaObject,
        igBasicColorChanger_Register,
        igBasicColorChanger_GetPublishedMetaObject,
        thunk_igOnOffColorChanger_GetMetaObject,
        igOnOffColorChanger_className,
        0x58, /* instance size */
        igOnOffColorChanger_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
