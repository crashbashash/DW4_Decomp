extern char igTextElement_GetVTable[];
extern char thunk_igTextElement_GetMetaObject[];
extern char igGeometryElement_GetPublishedMetaObject[];
extern char igGeometryElement_Register[];
extern char g_igTextElement_callbackList[];
extern char igTextElement_className[];
extern char g_igTextElement_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();
int igTextElement_InitFields();

void igTextElement_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTextElement_metaObject,
        igGeometryElement_Register,
        igGeometryElement_GetPublishedMetaObject,
        thunk_igTextElement_GetMetaObject,
        igTextElement_className,
        0x38, /* instance size */
        igTextElement_GetVTable,
        &igTextElement_InitFields,
        0, /* extra callback item */
        g_igTextElement_callbackList /* callback list */
    );
}
