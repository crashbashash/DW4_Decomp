extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igEventReceiver_GetVTable[];
extern char thunk_igEventReceiver_GetMetaObject[];
extern char igEventReceiver_className[];
extern char g_igEventReceiver_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igEventReceiver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventReceiver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEventReceiver_GetMetaObject,
        igEventReceiver_className,
        8, /* instance size */
        igEventReceiver_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
