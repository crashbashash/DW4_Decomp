/* 0x002a8998 — FUN_002a8998 (152 bytes). Under the guard, returns the second-best picture slot (FUN_002a8a30) while the player runs (+72 == 4), dropping it when option 15 is set and FUN_002af6c0 rejects its f56/f60. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_002a0e70();
void FUN_002a0e88();
void FUN_002a8a30();
int FUN_002adc40();
int FUN_002af6c0();

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
struct Player2a8998 {
    char pad0[72];
    int f72;                              /* 4 = running */
};

/* Under the guard, returns the second-best slot from FUN_002a8a30, or 0 when not running or FUN_002af6c0 rejects it. */
struct Slot *FUN_002a8998(struct Player2a8998 *player) {
    int guard;
    struct Slot *best;
    struct Slot *second;

    FUN_002a0e70(&guard);
    if (player->f72 != 4) {
        second = 0;
    } else {
        FUN_002a8a30(player, &best, &second);
        if (second != 0 && FUN_002adc40(player, 15) != 0) {
            if (FUN_002af6c0(player, second->f56, second->f60) == 0) {
                second = 0;
            }
        }
    }
    FUN_002a0e88(&guard);
    return second;
}
