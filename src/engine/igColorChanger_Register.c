extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igColorChanger_GetVTable[];
extern char thunk_igColorChanger_GetMetaObject[];
extern char igColorChanger_className[];
extern char g_igColorChanger_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igColorChanger_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igColorChanger_GetMetaObject,
        igColorChanger_className,
        8, /* instance size */
        igColorChanger_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
