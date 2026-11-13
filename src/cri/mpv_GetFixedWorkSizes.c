/* Reports two fixed buffer sizes (0x4000 and 0x700 bytes) through the out-pointers and returns their sum;
 * FUN_00291b70 adds it to the other work-area sizes. The handle is unused. */

/* The stores go through a statement macro (do/while(0)); its loop notes keep sched1/sched2 from hoisting
 * the second constant above the first store. */
#define SET_SIZE(p, v) do { *(p) = (v); } while (0)

int mpv_GetFixedWorkSizes(int handle, int *size_a, int *size_b) {
    SET_SIZE(size_a, 0x4000);
    SET_SIZE(size_b, 0x700);
    return *size_a + *size_b;
}
