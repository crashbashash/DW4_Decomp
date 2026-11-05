/* 0x0023d070 — FUN_0023d070. Banked by tools/retype_struct_member.py (shape: leadfn1):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
int lua_pushnil();
int lua_pushstring();

void FUN_0023d070(int dummy0, int arg1, int arg2) {
    if (arg2 != 0) {
        lua_pushstring(arg1, arg2);
        return;
    }
    lua_pushnil(arg1);
}
