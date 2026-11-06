extern char igView_Register[];
extern char igView_GetPublishedMetaObject[];
extern char igFieldChangeView_GetVTable[];
extern char thunk_igFieldChangeView_GetMetaObject[];
extern char g_igFieldChangeView_callbackList[];
extern char igFieldChangeView_className[];
extern char g_igFieldChangeView_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igFieldChangeView_InitFields();

void igFieldChangeView_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFieldChangeView_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igFieldChangeView_GetMetaObject,
        igFieldChangeView_className,
        0x14, /* instance size */
        igFieldChangeView_GetVTable,
        &igFieldChangeView_InitFields,
        0, /* extra callback item */
        g_igFieldChangeView_callbackList /* callback list */
    );
}
