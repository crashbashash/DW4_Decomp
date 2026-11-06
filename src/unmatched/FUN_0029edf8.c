/* Under the guard, adds amount to the running total at +3368+356 and records the new total in the
 * 32-entry history slot for the incremented count. */
void FUN_002a0e70();
void FUN_002a0e88();

/* Running total with a 32-entry history of past totals. */
struct Tally {
    char pad0[356];
    int total;                            /* +356 */
    int count;                            /* +360 */
    int history[32];                      /* +364 */
};
struct Owner29edf8 {
    char pad0[3368];
    struct Tally tally;                   /* +3368 */
};

/* matching construct: manual — declared int with no return statement (implicit-int style), which keeps the final call a jal */
int FUN_0029edf8(struct Owner29edf8 *owner, int amount) {
    char guard[16];
    struct Tally *tally = &owner->tally;
    int total;
    int count;

    FUN_002a0e70(guard);
    total = tally->total + amount;
    count = tally->count;
    count++; /* matching construct: manual — separate increment stops count + 1 + 31 folding into + 32 */
    tally->total = total;
    tally->history[count % 32] = total;
    tally->count = count;
    FUN_002a0e88(guard);
}
