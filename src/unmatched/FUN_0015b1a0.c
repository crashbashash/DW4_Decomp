/* arg1 is unused but must stay: the value arrives in the third parameter (a2), and a two-parameter
 * spelling would put it in a1. */
int FUN_0015b1a0(int arg0, int arg1, int arg2) {
    return *(int *)((char *)(arg0) + 12) + (arg2 * 2);
}
