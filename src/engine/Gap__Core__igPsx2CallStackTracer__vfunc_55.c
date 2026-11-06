/* 0x003295b0
 * Raw lower bound of the address range the tracer pages over (a hypothesis from the
 * sibling vfuncs): the word at 0x004c2610, the same start vfunc_52 returns after
 * mapping the all-ones "unset" value to 0. */
extern int g_rangeStart[4];
int Gap__Core__igPsx2CallStackTracer__vfunc_55(void) {
    return g_rangeStart[0];
}
