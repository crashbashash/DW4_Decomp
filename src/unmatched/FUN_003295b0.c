/* Raw lower bound of the address range the tracer pages over, the same start FUN_00329570 returns
 * after mapping the all-ones "unset" value to 0. */
extern int g_rangeStart[4];
int FUN_003295b0(void) {
    return g_rangeStart[0];
}
