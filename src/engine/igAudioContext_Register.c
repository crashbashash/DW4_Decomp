extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igAudioContext_GetMetaObject[];
extern char igObject_Register[];
extern char igAudioContext_className[];
extern char g_igAudioContext_metaObject[];
int AudioLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAudioContext_InitFields();

void igAudioContext_Register(void) {
    AudioLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAudioContext_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAudioContext_GetMetaObject,
        igAudioContext_className,
        0xC, /* instance size */
        0,
        &igAudioContext_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
