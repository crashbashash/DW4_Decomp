/* 0x0010dae0 — FUN_0010dae0 (36 bytes). Calls FUN_0010d460, then clears the word D_00481e70. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0010d460(void);
extern int D_00481e70;

void FUN_0010dae0(void) {
    FUN_0010d460();
    do { } while (0); /* matching construct: permuter — empty loop after the call splits the scheduling region, so ld ra is not hoisted above the store */
    D_00481e70 = 0;
}
