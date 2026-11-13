/* The game's lua_dofile: Lua's own reads through stdio, this one through an igFile. */
int lua_dofile(lua_State *L, const char *filename) {
    igSmartPointer<igFileView> file(igFile_Create(0), AdoptReference());
    int size;
    char *buffer;
    int result;

    if (file.p->open(filename, "rb") == 0) {
        return LUA_ERRFILE;
    }
    file.p->seek(0, SEEK_END);
    size = file.p->size();
    buffer = (char *)luaM_realloc(L, 0, size);
    if (buffer == 0) {
        file.p->close();
        return LUA_ERRMEM;
    }
    file.p->seek(0, SEEK_SET);
    file.p->read(buffer, size, 1);
    file.p->close();
    result = lua_dobuffer(L, buffer, size, filename);
    luaM_realloc(L, buffer, 0);
    return result;
}
