/* 0x00294a40 — FUN_00294a40 (24 bytes). Error-callback adapter: reports `msg` through FUN_0029a320, ignoring the context argument. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
extern void FUN_0029a320(const char *msg);

void FUN_00294a40(void *ctx, const char *msg) {
    FUN_0029a320(msg);
}
