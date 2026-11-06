/* Error stub: sets the per-thread error code (FUN_00124d50 returns its address) to 5 and fails
 * with -1. */
int *FUN_00124d50(void);

int FUN_0010b708(void) {
    int *error_code = FUN_00124d50();

    do { } while (0); /* matching construct: permuter — empty loop after the call splits the scheduling region, so ld ra is not hoisted above the store setup */
    *error_code = 5;
    return -1;
}
