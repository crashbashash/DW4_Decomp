/* Wires the chain 1→2→3, then either 3→4→5→6 (when the option word at +16 is set) or 3→6 directly,
 * alternating FUN_002b0268 and FUN_002b01a8 links. */
int FUN_002b01a8();
int FUN_002b0268();

struct Options {
    char pad[16];
    int f16;                              /* non-zero: FUN_002b0048 inserts its optional stage */
    int f20;                              /* non-zero: FUN_002b00e8 inserts its optional stage */
};

void FUN_002b0048(char *ctx, struct Options *options) {
    FUN_002b0268(ctx, 1, 2);
    FUN_002b01a8(ctx, 2, 3);
    if (options->f16 != 0) {
        FUN_002b0268(ctx, 3, 4);
        FUN_002b01a8(ctx, 4, 5);
        FUN_002b0268(ctx, 5, 6);
        return;
    }
    FUN_002b0268(ctx, 3, 6);
}
