/* Calls FUN_00125d78 with both arguments and a 16-byte scratch area on the stack, returning its
 * result. */
int FUN_00125d78(void *state, void *arg, void *scratch);

int FUN_00125ec0(void *state, void *arg) {
    int scratch[4];

    return FUN_00125d78(state, arg, scratch);
}
