extern unsigned char g_LuaLibrary_registered[4];
void LuaLibrary_MarkRegistered(void) {
    if (g_LuaLibrary_registered[0] == 0) {
        g_LuaLibrary_registered[0] = 1;
    }
}
