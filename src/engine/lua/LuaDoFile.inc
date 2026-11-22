/* The game's lua_dofile: Lua's own reads through stdio, this one through an igFile. */
int lua_dofile(lua_State *L, const char *filename) {
    igSmartPointer<Gap::Core::igFile> file(Gap::Core::igFile::_instantiateFromPool(0), AdoptReference());
    int size;
    char *buffer;
    int result;

    if (file.p->fopen(filename, "rb") == 0) {
        return LUA_ERRFILE;
    }
    file.p->fseek(0, SEEK_END);
    size = file.p->ftell();
    buffer = (char *)luaM_realloc(L, 0, size);
    if (buffer == 0) {
        file.p->fclose();
        return LUA_ERRMEM;
    }
    file.p->fseek(0, SEEK_SET);
    file.p->fread(buffer, size, 1);
    file.p->fclose();
    result = lua_dobuffer(L, buffer, size, filename);
    luaM_realloc(L, buffer, 0);
    return result;
}
