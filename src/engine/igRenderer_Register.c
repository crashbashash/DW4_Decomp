extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char thunk_igRenderer_GetMetaObject[];
extern char g_igRenderer_callbackList[];
extern char igRenderer_className[];
extern char g_igRenderer_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igRenderer_InitFields();

void igRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igRenderer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRenderer_GetMetaObject,
        igRenderer_className,
        0xC, /* instance size */
        0,
        &igRenderer_InitFields,
        0, /* extra callback item */
        g_igRenderer_callbackList /* callback list */
    );
}
