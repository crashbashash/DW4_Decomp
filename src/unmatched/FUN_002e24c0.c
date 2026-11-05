/* 0x002e24c0 - FUN_002e24c0. Guarded indexed load. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
int FUN_002e24c0(int arg0, int arg1) {
    int r = 0; if (arg1 < 0x10) { r = arg1 * 4; r += arg0; r = *(int *)((char *)r + 84); } return r;
}
