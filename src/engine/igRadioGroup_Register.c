extern char igObject_GetMetaObject_ParentAccessor[];
extern char igObject_Register[];
extern char igRadioGroup_GetVTable[];
extern char thunk_igRadioGroup_GetMetaObject[];
extern char g_igRadioGroup_callbackList[];
extern char igRadioGroup_className[];
extern char g_igRadioGroup_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igRadioGroup_InitFields();

void igRadioGroup_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRadioGroup_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRadioGroup_GetMetaObject,
        igRadioGroup_className,
        0x20, /* instance size */
        igRadioGroup_GetVTable,
        &igRadioGroup_InitFields,
        0, /* extra callback item */
        g_igRadioGroup_callbackList /* callback list */
    );
}
