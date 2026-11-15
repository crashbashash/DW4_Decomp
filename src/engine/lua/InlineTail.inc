inline igMetaObject *igLuaGlue::getMeta() {
    return g_igLuaGlue_metaObject;
}

inline void igLuaGlue::userConstruct() {
    LuaGlue_Initialize();
}

inline void igLuaGlue::userDestruct() {
    LuaGlue_Shutdown();
}
