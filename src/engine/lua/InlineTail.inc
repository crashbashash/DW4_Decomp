inline igMetaObject *igLuaGlue::getMeta() const {
    return g_igLuaGlue_metaObject;
}

inline void igLuaGlue::userConstruct(int flag) {
    LuaGlue_Initialize();
}

inline void igLuaGlue::userDestruct() {
    LuaGlue_Shutdown();
}
