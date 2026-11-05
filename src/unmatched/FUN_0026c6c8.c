/* 0x0026c6c8 - FUN_0026c6c8. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
int FUN_002607e8();
extern int DAT_004ee850[4];
short FUN_0026c6c8(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004ee850[0]);
        return 0;
    }
    return *(int *)((char *)(arg0) + 64);
}
