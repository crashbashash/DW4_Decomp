/* 0x002a8a30 — FUN_002a8a30 (252 bytes). Picks the best and second-best slots holding a picture (state 2 or 4), ranked by FUN_002a8b30; clears them when fewer are held. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002a8b30();

/* One 232-byte decode slot. */
struct Slot {
    int state;                            /* 2/4 = holding a picture */
    char pad4[56 - 4];
    int f56;
    int f60;
    char pad64[232 - 64];
};
struct Context {
    char pad0[376];
    int slotCount;                        /* +376 */
    int pad380;
    struct Slot slots[16];                /* +384 */
};
struct Player2a8a30 {
    char pad0[8120];
    void *context;                        /* +8120 */
};

/* Picks the best and second-best slots holding a picture (state 2 or 4), ranked by FUN_002a8b30. */
/* matching construct: manual — out-parameters and the context link are void * (same alias set), which keeps the clearing stores after the context load */
void FUN_002a8a30(struct Player2a8a30 *player, void **best, void **second) {
    struct Context *context;
    struct Slot *slot;
    int held = 0;
    int i;
    int n;

    context = (struct Context *)player->context;
    *best = 0;
    *second = 0;
    n = context->slotCount;
    slot = context->slots;
    for (i = 0; i < n; i++) {
        if (slot->state == 2 || slot->state == 4) {
            held++;
            if (FUN_002a8b30(*best, slot) != 0) {
                *second = *best;
                *best = slot;
            } else if (FUN_002a8b30(*second, slot) != 0) {
                *second = slot;
            }
        }
        slot++;
    }
    if (held <= 0) {
        *best = 0;
        *second = 0;
    } else if (held == 1) {
        *second = 0;
    }
}
