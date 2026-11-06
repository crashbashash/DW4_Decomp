/* Counts the context slots in state 2 or 4 under the guard; returns -1 instead of 0 when context
 * f124 is 1. */
void FUN_002a0e70();
void FUN_002a0e88();

/* One 232-byte decode slot. */
struct Slot {
    int state;                            /* 2/4 = holding a picture */
    char pad4[232 - 4];
};
struct Context {
    char pad0[124];
    int f124;
    char pad128[376 - 128];
    int slotCount;                        /* +376 */
    int pad380;
    struct Slot slots[16];                /* +384 */
};
struct Player2a8500 {
    char pad0[8120];
    struct Context *context;              /* +8120 */
};

/* Counts slots in state 2 or 4 under the guard; -1 instead of 0 when context f124 is 1. */
int FUN_002a8500(struct Player2a8500 *player) {
    char guard[16];
    struct Context *context;
    struct Slot *slot;
    int count;
    int i;
    int n;

    FUN_002a0e70(guard);
    context = player->context;
    count = 0;
    slot = context->slots;
    n = context->slotCount;
    for (i = 0; i < n; i++) {
        if (slot->state == 2 || slot->state == 4) {
            count++;
        }
        slot++;
    }
    if (context->f124 == 1 && count == 0) {
        count = -1;
    }
    FUN_002a0e88(guard);
    return count;
}
