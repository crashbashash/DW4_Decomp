/* Lower bound of the address range the tracer pages over, or 0 while it still holds the all-ones
 * "unset" value. vfunc_57 reports `v - start` and `end - start` against the upper bound, and
 * vfunc_61 walks pages from the start bound to that end. vfunc_55 is the raw getter without the -1
 * test. */
extern int g_rangeStart[4];
int Gap__Core__igPsx2CallStackTracer__vfunc_52(void) {
    int start;

    start = g_rangeStart[0];
    if (start == -1) {
        start = 0;
    }
    return start;
}
