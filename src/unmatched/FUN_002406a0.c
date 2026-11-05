/* 0x002406a0 — FUN_002406a0. m2c draft (build/m2c/FUN_002406a0.c), call-argument/cleaner fix-up; verified byte-identical by
 * tools/verify.py (loop: tools/m2c_loop.py). */
int FUN_0023ec50();
int lua_touserdata();

void FUN_002406a0(int arg0) {
    FUN_0023ec50(lua_touserdata(arg0, -1), arg0);
}
