/* Non-reentrant front end of FUN_00125ec0's operation: calls FUN_00125d78 on the global state
 * block D_004854a0 with the argument and a 16-byte scratch area on the stack. */
extern void *D_004854a0;    /* current C-library state block (also returned by FUN_00124d50) */
int FUN_00125d78(void *state, void *arg, void *scratch);

int FUN_00125d50(void *arg) {
    int scratch[4];

    return FUN_00125d78(D_004854a0, arg, scratch);
}
