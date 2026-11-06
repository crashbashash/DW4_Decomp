extern char igVisualContext_Register[];
extern char thunk_igPsx2VisualContext_GetMetaObject[];
extern char igPsx2VisualContext_GetVTable[];
extern char igVisualContext_GetPublishedMetaObject[];
extern char g_igPsx2VisualContext_callbackList[];
extern char igPsx2VisualContext_className[];
extern char g_igPsx2VisualContext_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2VisualContext_InitFields();

void igPsx2VisualContext_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2VisualContext_metaObject,
        igVisualContext_Register,
        igVisualContext_GetPublishedMetaObject,
        thunk_igPsx2VisualContext_GetMetaObject,
        igPsx2VisualContext_className,
        0x618, /* instance size */
        igPsx2VisualContext_GetVTable,
        &igPsx2VisualContext_InitFields,
        0, /* extra callback item */
        g_igPsx2VisualContext_callbackList /* callback list */
    );
}
