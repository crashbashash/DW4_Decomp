extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char thunk_igGeometryElement_GetMetaObject[];
extern char g_igGeometryElement_callbackList[];
extern char igGeometryElement_className[];
extern char g_igGeometryElement_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igGeometryElement_InitFields();

void igGeometryElement_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igGeometryElement_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igGeometryElement_GetMetaObject,
        igGeometryElement_className,
        0x2C, /* instance size */
        0,
        &igGeometryElement_InitFields,
        0, /* extra callback item */
        g_igGeometryElement_callbackList /* callback list */
    );
}
