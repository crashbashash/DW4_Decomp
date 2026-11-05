/* 0x002977a8 — FUN_002977a8 (24 bytes). Error-callback adapter: reports `msg` through FUN_0029a320, ignoring the context argument. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_0029a320(const char *msg);

void FUN_002977a8(void *ctx, const char *msg) {
    FUN_0029a320(msg);
}
