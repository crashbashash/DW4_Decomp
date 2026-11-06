/* Calls FUN_00262748 with its first three arguments, a 16-byte scratch area on the stack, and its
 * last two arguments. */
int FUN_00262748(int a0, int a1, int a2, void *scratch, int a4, int a5);

int FUN_00262720(int a0, int a1, int a2, int a4, int a5) {
    int scratch[4];

    return FUN_00262748(a0, a1, a2, scratch, a4, a5);
}
