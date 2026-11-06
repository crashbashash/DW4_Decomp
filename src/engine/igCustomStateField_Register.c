extern char igNamedObject_GetPublishedMetaObject[];
extern char igCustomStateField_GetVTable[];
extern char thunk_igCustomStateField_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igCustomStateField_callbackList[];
extern char igCustomStateField_className[];
extern char g_igCustomStateField_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igCustomStateField_InitFields();

void igCustomStateField_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCustomStateField_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igCustomStateField_GetMetaObject,
        igCustomStateField_className,
        0x14, /* instance size */
        igCustomStateField_GetVTable,
        &igCustomStateField_InitFields,
        0, /* extra callback item */
        g_igCustomStateField_callbackList /* callback list */
    );
}
