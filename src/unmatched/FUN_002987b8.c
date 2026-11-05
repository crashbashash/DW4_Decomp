/* 0x002987b8 — FUN_002987b8 (120 bytes). Builds the frame-conversion parameters for `frame` (FUN_00297838) and runs the converter FUN_002b3db0 on the player's decoder with two extra arguments. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void *FUN_00297810(void *player);
void FUN_00297838(void *player, int *frame, void *params);
void FUN_002b3db0(void *decoder, void *params, int a, int b);

struct Params002987b8 {
    int word[36];
};

void FUN_002987b8(void *player, int *frame, int a, int b) {
    struct Params002987b8 params;
    void *decoder = FUN_00297810(player);

    FUN_00297838(player, frame, &params);
    FUN_002b3db0(decoder, &params, a, b);
}
