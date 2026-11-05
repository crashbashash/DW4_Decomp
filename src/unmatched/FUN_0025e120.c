/* 0x0025e120 — FUN_0025e120 (44 bytes). Copies `count` 16-bit values from src to dst. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0025e120(unsigned short *dst, const unsigned short *src, int count) {
    while (count > 0) {
        *dst++ = *src++;
        count--;
    }
}
