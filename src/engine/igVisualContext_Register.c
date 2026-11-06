extern char thunk_igVisualContext_GetMetaObject[];
extern char igContext_GetPublishedMetaObject[];
extern char igContext_Register[];
extern char g_igVisualContext_callbackList[];
extern char igVisualContext_className[];
extern char g_igVisualContext_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igVisualContext_InitFields();

void igVisualContext_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igVisualContext_metaObject,
        igContext_Register,
        igContext_GetPublishedMetaObject,
        thunk_igVisualContext_GetMetaObject,
        igVisualContext_className,
        0x140, /* instance size */
        0,
        &igVisualContext_InitFields,
        0, /* extra callback item */
        g_igVisualContext_callbackList /* callback list */
    );
}
