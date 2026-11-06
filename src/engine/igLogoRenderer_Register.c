extern char igRenderer_GetPublishedMetaObject[];
extern char igRenderer_Register[];
extern char igLogoRenderer_GetVTable[];
extern char thunk_igLogoRenderer_GetMetaObject[];
extern char g_igLogoRenderer_callbackList[];
extern char igLogoRenderer_className[];
extern char g_igLogoRenderer_metaObject[];
int igMetaObject_RegisterClass();
int ViewerLibrary_MarkRegistered();
int igLogoRenderer_InitFields();

void igLogoRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLogoRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igLogoRenderer_GetMetaObject,
        igLogoRenderer_className,
        0x28, /* instance size */
        igLogoRenderer_GetVTable,
        &igLogoRenderer_InitFields,
        0, /* extra callback item */
        g_igLogoRenderer_callbackList /* callback list */
    );
}
