void LuaLibrary_MarkRegistered(void) {
    if (g_LuaLibrary_registered == 0) {
        g_LuaLibrary_registered = 1;
    }
}
