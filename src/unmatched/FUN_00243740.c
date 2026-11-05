/* 0x00243740 — 40 bytes. Wrapper over lua_touserdata: forwards its own first argument (in a0)
 * as lua_touserdata's FIRST argument and passes the literal 1 as the second. Retail
 * leaves a0 untouched and emits `li a1,1`; the naive one-argument C spelling emits
 * `li a0,1` and misses by one register. */
int FUN_001005f0();
int lua_touserdata();

int FUN_00243740(int self) {
    FUN_001005f0(lua_touserdata(self, 1));
    return 0;
}
