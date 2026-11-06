/* Lower bound of the address range the tracer pages over, or 0 while it still holds the all-ones
 * "unset" value. FUN_003295d0 reports `v - start` and `end - start` against the upper bound, and
 * FUN_00329980 walks pages from the start bound to that end. FUN_003295b0 is the raw getter without the -1
 * test. */
extern int g_rangeStart[4];
int FUN_00329570(void) {
    int start;

    start = g_rangeStart[0];
    if (start == -1) {
        start = 0;
    }
    return start;
}
