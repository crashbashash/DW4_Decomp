/* 0x0025e1c0 — FUN_0025e1c0 (32 bytes). Copies count halfwords from buffer+offset to the start of buffer; the third argument is unused. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
/* FUN_0025e120 (0x25e120): copies count halfwords from src to dst. */
void FUN_0025e120(short *dst, short *src, int count);

void FUN_0025e1c0(short *buffer, int offset, int unused, int count) {
    FUN_0025e120(buffer, buffer + offset, count);
}
