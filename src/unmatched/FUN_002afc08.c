/* 0x002afc08 — FUN_002afc08 (152 bytes). Copies a 60-byte record from `src` to `dst`, then resets the source through FUN_002afcb8(src, 0). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Record60 {
    int words[15];
};

void FUN_002afcb8(struct Record60 *rec, int value);

void FUN_002afc08(struct Record60 *dst, struct Record60 *src) {
    *dst = *src;
    FUN_002afcb8(src, 0);
}
