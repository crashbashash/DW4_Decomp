/* 0x002b0208 — FUN_002b0208 (28 bytes). Links entry44[from] output slot 2 to entry74[to] through FUN_002b0228. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b0228();

void FUN_002b0208(char *ctx, int from, int to) {
    FUN_002b0228(ctx, from, 2, to);
}
