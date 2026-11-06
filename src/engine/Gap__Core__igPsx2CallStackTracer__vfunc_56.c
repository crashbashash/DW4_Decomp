/* Raw upper bound of the address range the tracer pages over: the end that vfunc_57 reports as
 * `end - start` and vfunc_61 walks up to. Unlike vfunc_52 there is no -1 test. */
extern int g_rangeEnd[4];
int Gap__Core__igPsx2CallStackTracer__vfunc_56(void) {
    return g_rangeEnd[0];
}
