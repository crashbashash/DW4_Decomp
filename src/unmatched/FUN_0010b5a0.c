/* 0x0010b5a0 — FUN_0010b5a0 (40 bytes). Error stub: sets the per-thread error code (FUN_00124d50 returns its address) to 5 and fails with -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int *FUN_00124d50(void);

int FUN_0010b5a0(void) {
    int *error_code = FUN_00124d50();

    do { } while (0); /* matching construct: permuter — empty loop after the call splits the scheduling region, so ld ra is not hoisted above the store setup */
    *error_code = 5;
    return -1;
}
