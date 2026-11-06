extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char thunk_igAction_GetMetaObject[];
extern char igAction_className[];
extern char g_igAction_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igAction_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAction_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAction_GetMetaObject,
        igAction_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
