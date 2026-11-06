/* Raw upper bound of the address range the tracer pages over: the end that FUN_003295d0 reports as
 * `end - start` and FUN_00329980 walks up to. Unlike FUN_00329570 there is no -1 test. */
extern int g_rangeEnd[4];
int FUN_003295c0(void) {
    return g_rangeEnd[0];
}
