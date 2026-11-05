/* 0x00244a50 — FUN_00244a50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004ea530[];
int lua_settop();
int lua_type();
int lua_touserdata();
int lua_pushstring();
int lua_rawget();

int FUN_00244a50(int arg0, int arg1) {
    int temp_s0;

    if (lua_type() != 4) {
        return 0;
    }
    lua_pushstring(arg0, DAT_004ea530);
    lua_rawget(arg0, arg1);
    temp_s0 = lua_touserdata(arg0, -1);
    lua_settop(arg0, -2);
    return temp_s0;
}
