extern char igObject_GetMetaObject_ParentAccessor[];
extern char igLuaGlue_GetVTable[];
extern char thunk_igLuaGlue_GetMetaObject[];
extern char igObject_Register[];
extern char igLuaGlue_className[];
extern char g_igLuaGlue_metaObject[];
int LuaLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igLuaGlue_Register(void) {
    LuaLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLuaGlue_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igLuaGlue_GetMetaObject,
        igLuaGlue_className,
        8, /* instance size */
        igLuaGlue_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
