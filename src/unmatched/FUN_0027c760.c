/* matching construct: one expression; the unit compiler (Sony EE GCC 2.96 -O2 -G0) keeps the index arithmetic in the argument register only when it is not written back to the parameter step by step */
int FUN_0027c760(char *arg0, int arg1, int arg2) {
    return *(int *)(arg0 + (arg1 * 2 + arg2) * 4 + 40);
}
