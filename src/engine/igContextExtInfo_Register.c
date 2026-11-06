extern char igObject_GetMetaObject_ParentAccessor[];
extern char igContextExtInfo_GetVTable[];
extern char thunk_igContextExtInfo_GetMetaObject[];
extern char igObject_Register[];
extern char g_igContextExtInfo_callbackList[];
extern char igContextExtInfo_className[];
extern char g_igContextExtInfo_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igContextExtInfo_InitFields();

void igContextExtInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igContextExtInfo_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igContextExtInfo_GetMetaObject,
        igContextExtInfo_className,
        0x14, /* instance size */
        igContextExtInfo_GetVTable,
        &igContextExtInfo_InitFields,
        0, /* extra callback item */
        g_igContextExtInfo_callbackList /* callback list */
    );
}
