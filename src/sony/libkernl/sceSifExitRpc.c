void FUN_0010d460(void);
extern int D_00481e70;

void sceSifExitRpc(void) {
    FUN_0010d460();
    do { } while (0); /* matching construct: permuter — empty loop after the call splits the scheduling region, so ld ra is not hoisted above the store */
    D_00481e70 = 0;
}
