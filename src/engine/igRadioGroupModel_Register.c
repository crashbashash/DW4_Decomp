extern char igRadioGroupModel_GetVTable[];
extern char thunk_igRadioGroupModel_GetMetaObject[];
extern char igModel_GetPublishedMetaObject[];
extern char igModel_Register[];
extern char igRadioGroupModel_className[];
extern char g_igRadioGroupModel_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igRadioGroupModel_InitFields();

void igRadioGroupModel_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRadioGroupModel_metaObject,
        igModel_Register,
        igModel_GetPublishedMetaObject,
        thunk_igRadioGroupModel_GetMetaObject,
        igRadioGroupModel_className,
        0x10, /* instance size */
        igRadioGroupModel_GetVTable,
        &igRadioGroupModel_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
