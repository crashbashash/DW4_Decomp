int lua_error();
int luaM_realloc();
int luaO_power2();

int luaM_growaux(int arg0, int arg1, unsigned int arg2, int arg3, int arg4, int arg5, int arg6) {
    unsigned int temp_s0;

    temp_s0 = arg2 + arg3;
    if (arg2 >= (unsigned int) (arg6 - arg3)) {
        lua_error(arg0, arg5);
    }
    if (arg2 >= (unsigned int) (temp_s0 ^ arg2) || (arg2 != 0 && temp_s0 < 4U)) {
        return arg1;
    }
    return luaM_realloc(arg0, arg1, arg4 * luaO_power2(temp_s0));
}
