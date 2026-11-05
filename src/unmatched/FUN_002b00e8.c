/* 0x002b00e8 — FUN_002b00e8 (156 bytes). Wires the chain 2→3→4, then either 4→5→6→7 (when the option word at +20 is set) or 4→7 directly, alternating FUN_002b0268 and FUN_002b01a8 links. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b01a8();
int FUN_002b0268();

struct Options {
    char pad[16];
    int f16;                              /* non-zero: FUN_002b0048 inserts its optional stage */
    int f20;                              /* non-zero: FUN_002b00e8 inserts its optional stage */
};

void FUN_002b00e8(char *ctx, struct Options *options) {
    FUN_002b0268(ctx, 2, 3);
    FUN_002b01a8(ctx, 3, 4);
    if (options->f20 != 0) {
        FUN_002b0268(ctx, 4, 5);
        FUN_002b01a8(ctx, 5, 6);
        FUN_002b0268(ctx, 6, 7);
        return;
    }
    FUN_002b0268(ctx, 4, 7);
}
