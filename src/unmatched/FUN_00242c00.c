/* The first argument is forwarded untouched in a0 and the literal 1 goes in a1; the one-argument
 * spelling would load 1 into a0. */
int FUN_001005f0();
int lua_touserdata();

int FUN_00242c00(int self) {
    FUN_001005f0(lua_touserdata(self, 1));
    return 0;
}
