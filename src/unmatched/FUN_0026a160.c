/* 0x0026a160 - FUN_0026a160. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
int FUN_0026a160(void *arg0) {
    int var_v0;

    var_v0 = 0;
    if (*(int *)((char *)(arg0) + 8) != 0) {
        var_v0 = *(int *)((char *)(arg0) + 88);
    }
    return var_v0;
}
