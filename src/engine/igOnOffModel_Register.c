extern char igGuiComponentModel_GetPublishedMetaObject[];
extern char igOnOffModel_GetVTable[];
extern char thunk_igOnOffModel_GetMetaObject[];
extern char igGuiComponentModel_Register[];
extern char igOnOffModel_className[];
extern char g_igOnOffModel_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igOnOffModel_InitFields();

void igOnOffModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffModel_metaObject,
        igGuiComponentModel_Register,
        igGuiComponentModel_GetPublishedMetaObject,
        thunk_igOnOffModel_GetMetaObject,
        igOnOffModel_className,
        0x28, /* instance size */
        igOnOffModel_GetVTable,
        &igOnOffModel_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
