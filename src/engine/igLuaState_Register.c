extern char igNamedObject_GetPublishedMetaObject[];
extern char igLuaState_GetVTable[];
extern char thunk_igLuaState_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igLuaState_callbackList[];
extern char igLuaState_className[];
extern char g_igLuaState_metaObject[];
int LuaLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLuaState_InitFields();

void igLuaState_Register(void) {
    LuaLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLuaState_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igLuaState_GetMetaObject,
        igLuaState_className,
        0x14, /* instance size */
        igLuaState_GetVTable,
        &igLuaState_InitFields,
        0, /* extra callback item */
        g_igLuaState_callbackList /* callback list */
    );
}
