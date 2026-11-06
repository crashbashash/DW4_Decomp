/* Under the guard, runs FUN_0029f200 on the state and derives its two flag bytes from the words at
 * +8/+12/+16. */
void FUN_0029f200();
void FUN_002a0e70();
void FUN_002a0e88();

struct State29f160 {
    char f0;                              /* set when +8/+12 are non-zero or +16 is -1 */
    char f1;                              /* set when +8/+12 are non-zero */
    char pad2[8 - 2];
    int f8;
    int f12;
    int f16;
};

/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
int FUN_0029f160(void *owner, int index, struct State29f160 *state) {
    char guard[16];

    FUN_002a0e70(guard);
    FUN_0029f200(owner, index, state);
    if (state->f8 != 0 || state->f12 != 0 || state->f16 == -1) {
        state->f0 = 1;
    }
    if (state->f8 != 0 || state->f12 != 0) {
        state->f1 = 1;
    }
    FUN_002a0e88(guard);
}
