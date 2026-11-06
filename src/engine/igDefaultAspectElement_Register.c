extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igDefaultAspectElement_GetVTable[];
extern char thunk_igDefaultAspectElement_GetMetaObject[];
extern char g_igDefaultAspectElement_callbackList[];
extern char igDefaultAspectElement_className[];
extern char g_igDefaultAspectElement_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igDefaultAspectElement_InitFields();

void igDefaultAspectElement_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultAspectElement_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDefaultAspectElement_GetMetaObject,
        igDefaultAspectElement_className,
        0x20, /* instance size */
        igDefaultAspectElement_GetVTable,
        &igDefaultAspectElement_InitFields,
        0, /* extra callback item */
        g_igDefaultAspectElement_callbackList /* callback list */
    );
}
