/* 0x002a85a0 — FUN_002a85a0 (136 bytes). Claims the first free context slot under the guard and returns it, or 0 when all are in use. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002a0e70();
void FUN_002a0e88();

/* One 232-byte decode slot; the first doubleword is clear when the slot is free, and claiming it sets only the low word. */
struct Slot {
    union {
        long all;
        int flag;
    } inUse;
    char pad8[232 - 8];
};
struct Context {
    char pad0[376];
    int slotCount;                        /* +376 */
    int pad380;
    struct Slot slots[16];                /* +384 */
};
struct Player2a85a0 {
    char pad0[8120];
    struct Context *context;              /* +8120 */
};

/* Claims the first free slot under the guard; returns it, or 0 when all are in use. */
struct Slot *FUN_002a85a0(struct Player2a85a0 *player) {
    char guard[16];
    struct Context *context;
    struct Slot *slot;
    int count;
    int i;

    FUN_002a0e70(guard);
    context = player->context;
    i = 0;
    count = context->slotCount;
    slot = context->slots;
    for (; i < count; i++, slot++) {
        if (slot->inUse.all == 0) {
            slot->inUse.flag = 1;
            break;
        }
    }
    if (i == count) {
        slot = 0;
    }
    FUN_002a0e88(guard);
    return slot;
}
